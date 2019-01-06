// Fill out your copyright notice in the Description page of Project Settings.
#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float LaunchSpeed) const
{
	if (!Barrel)
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
		//UE_LOG(LogTemp, Warning, TEXT("%s's barrel at %s, is aiming at: %s with launch speed %f"), *GetOwner()->GetName(), *AimDirection.ToString(), *TargetLocation.ToString(), LaunchSpeed);
		// Move Barrel

	}
}

void UTankAimingComponent::AimBarrelTowards(const FVector AimDirection) const
{
	// Work out the difference between the current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator delta: %s"), *DeltaRotator.ToString());
	Barrel->Elevate(5); // TODO remove magic number from barrel elevation
}
