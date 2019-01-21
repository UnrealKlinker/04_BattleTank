// Copyright Paul Klinker, 2019.
#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * Used to rotate the tank turret
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) 
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is maximum counterclockwise speed and +1 is maximum clockwise speed
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreesPerSecond = 20; // Maximum turret rotation speed

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
