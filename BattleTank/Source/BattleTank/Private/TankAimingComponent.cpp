// Copyright Paul Klinker, 2019.
#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "../Public/Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


void UTankAimingComponent::AimAt(FVector TargetLocation, float LaunchSpeed) const
{
	if (!ensure(Barrel))
	{
		return;
	}

	FVector OutLaunchVelocity(0); // intialized to 0,0,0
	FVector StartLocation = Barrel->GetSocketLocation(FName("Muzzle")); // socket for the end of the barrel
	bool HighArc = false;
	float CollisionRadius = 0.f; // assume 120 mm cannon
	float OverrideGravity = 0.f; // 0 to not override gravity.
	bool DrawDebug = false;
	FCollisionResponseParams ResponseParam;
	TArray <AActor *>  ActorsToIgnore;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		GetWorld(),
		OutLaunchVelocity,
		StartLocation,
		TargetLocation,
		LaunchSpeed,
		HighArc,
		CollisionRadius,
		OverrideGravity,
		ESuggestProjVelocityTraceOption::DoNotTrace, /// currently need do not trace to prevent a bug
		ResponseParam,
		ActorsToIgnore);
	if (bHaveAimSolution)
	{
		// Calculate the out launch velocity
		// turn into a unit vector using . safe normal

		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		AimBarrelTowards(AimDirection);

		auto BarrelLocation = Barrel->GetComponentLocation();
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found, %s's barrel at %s, is aiming at: %s with launch speed %f"), Time, *GetOwner()->GetName(), *AimDirection.ToString(), *TargetLocation.ToString(), LaunchSpeed);
		// Move Barrel

	} 
	else
	{
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), Time);
	}
}

void UTankAimingComponent::AimBarrelTowards(const FVector AimDirection) const
{
	if (!ensure(Barrel) || !ensure(Turret))
	{
		UE_LOG(LogTemp, Warning, TEXT("Turret or Barrel is null"));
		return;
	}
	// Work out the difference between the current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch); // TODO remove magic number from barrel elevation

	// If the target is to the left then move the barrel in that direction, don't traverse all the way around
	if ((DeltaRotator.Yaw > 180) && (DeltaRotator.Yaw <= 360)) {
		float ReverseYaw = 360 - DeltaRotator.Yaw;
		Turret->Rotate(-ReverseYaw);
	}
	else {
		Turret->Rotate(DeltaRotator.Yaw);

	}

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator delta: %s"), *DeltaRotator.ToString());
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	if (!ensure(Barrel))
	{
		UE_LOG(LogTemp, Warning, TEXT("UTankAimingComponent barrel is missing in initialize."));
		return;
	}
	LastBarrelPosition = Barrel->GetForwardVector();

}

void UTankAimingComponent::AimAt(FVector TargetLocation)
{
	AimAt(TargetLocation, LaunchSpeed);
}

void UTankAimingComponent::Fire()
{
	// Fire a shell at the target
	if ((FiringStatus == EFiringStatus::EFS_Aiming) ||
		(FiringStatus == EFiringStatus::EFS_Locked))

	{
		if (!ensure(Barrel)) //TODO don't think I need this anymore since there is a check in BeginPlay
		{
			UE_LOG(LogTemp, Warning, TEXT("UTankAimingComponent barrel is missing."));
			return;
		}
		// Spawn a projectile a the barrel's muzzle socket.
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			*ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Muzzle")),
			Barrel->GetSocketRotation(FName("Muzzle")));
		if (!ensure(Projectile))
		{
			UE_LOG(LogTemp, Warning, TEXT("UTankAimingComponent projectile is missing."));
			return;
		}
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		CurrentAmmo--;
		if (CurrentAmmo <= 0) {
			FiringStatus = EFiringStatus::EFS_OutOfAmmo;
		}
		else {
			FiringStatus = EFiringStatus::EFS_Reloading;
		}
	}
}

FString UTankAimingComponent::GetAmmoAmount()
{
	return FString::FromInt(CurrentAmmo);
}

void UTankAimingComponent::BeginPlay()
{
	/// this prevents AI tanks from firing immediately upon spawning
	LastFireTime = FPlatformTime::Seconds();
	CurrentAmmo = AmmoCapacity;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	///UE_LOG(LogTemp, Warning, TEXT("UTankAimingComponent TickComponent DeltaTime %f"), DeltaTime);
	if (CurrentAmmo <= 0)
	{
		FiringStatus = EFiringStatus::EFS_OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) <  ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::EFS_Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::EFS_Aiming;
	} 
	else {
		FiringStatus = EFiringStatus::EFS_Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	bool BarrelMoving = true;
	/// get current barrel position
	FVector CurrentBarrelPosition = Barrel->GetForwardVector();
	/// compare to old position
	if (LastBarrelPosition.Equals(CurrentBarrelPosition, 0.011)) {
		BarrelMoving = false;
	}
	/// set old position to current position
	LastBarrelPosition = CurrentBarrelPosition;
	return BarrelMoving;
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}
