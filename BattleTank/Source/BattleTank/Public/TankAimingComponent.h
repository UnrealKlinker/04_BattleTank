// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel;
class UActorComponent;

// Used to aim the tank's cannon
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel *BarrelToSet);

	void AimAt(FVector TargetLocation, float LaunchSpeed) const;

protected:
	void AimBarrelTowards(FVector AimDirection) const;


private:
	UTankBarrel *Barrel = nullptr;


};
