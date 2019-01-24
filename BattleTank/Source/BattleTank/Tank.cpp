// Copyright Paul Klinker, 2019.

#include "Tank.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankMovementComponent.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/Projectile.h"

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
	// adds a component to the blueprint
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//	CreateComponentFromTemplate(UTankAimingComponent )
	
	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) {
		UE_LOG(LogTemp, Error, TEXT("TankAimingComponent is null in ATank constructor."));
	}
}

void ATank::AimAt(FVector TargetLocation)
{
	if (!ensure(TankAimingComponent)) {
		UE_LOG(LogTemp, Error, TEXT("TankAimingComponent is null, returning."));
		return;
	}

	TankAimingComponent->AimAt(TargetLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::Fire()
{
	if (!ensure(Barrel))
	{
		return;
	}

	bool isReloaded = ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds);
	// Fire a shell at the target
	if (isReloaded) {
		// Spawn a projectile a the barrel's muzzle socket.
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			*ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Muzzle")),
			Barrel->GetSocketRotation(FName("Muzzle")));
		if (!ensure(Projectile))
		{
			return;
		}
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
