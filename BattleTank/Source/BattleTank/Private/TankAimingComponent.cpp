// Fill out your copyright notice in the Description page of Project Settings.
#include "../Public/TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
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



void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
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
		UE_LOG(LogTemp, Warning, TEXT("%s's barrel at %s, is aiming at: %s with launch speed %f"), *GetOwner()->GetName(), *AimDirection.ToString(), *TargetLocation.ToString(), OutLaunchVelocity);
		// Move Barrel

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" %s, can't find a projectile velocity"), *GetOwner()->GetName());
	}
}

void UTankAimingComponent::AimBarrelTowards(const FVector AimDirection) const
{
	// Turn the turret and then elevate or depress the barrel
    // Use the blueprint to contrl the speed of the move - frame independent
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());
}
