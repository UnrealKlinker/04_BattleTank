// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankBarrel.generated.h"

class UStaticMeshComponent;

/**
 * Used to elevate the tank barrel
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) /// uyse hidecategories = ("Collision") to hide a category in the blueprint
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is maximum downward speed and +1 is maximum upward movement
	void Elevate(float RelativeSpeed);

private:
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20; // barrel elevation speed
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40; // Maximum elevation in degrees
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0; // Minimum elevation in degrees


};
