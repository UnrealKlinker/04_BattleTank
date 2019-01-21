// Copyright Paul Klinker, 2019.

#pragma once

#include "CoreMinimal.h"
#include "TankBarrel.generated.h"

class UStaticMeshComponent;

/**
 * Used to elevate the tank barrel
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) /// use hidecategories = ("Collision") to hide a category in the blueprint
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is maximum downward speed and +1 is maximum upward movement
	void Elevate(float RelativeSpeed);

private:
	
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreesPerSecond = 5; // barrel elevation speed
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxElevationDegrees = 40; // Maximum elevation in degrees
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MinElevationDegrees = 0; // Minimum elevation in degrees


};
