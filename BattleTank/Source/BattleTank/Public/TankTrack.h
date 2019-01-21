// Copyright Paul Klinker, 2019.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Used to maneuver the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public: 
	// Set a throttle value between -1 and +1
	UFUNCTION(BlueprintCallable, Category="Input")
	void SetThrottle(float Throttle);

	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 45007000.0; /// assume 40 Ton tank and 0-60 in 10 seconds. F=ma
};
