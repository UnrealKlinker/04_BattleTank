// Copyright Paul Klinker, 2019.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;
/**
 * Used to maneuver the tank
 * Look at: https://forums.unrealengine.com/community/work-in-progress/54936-assets-open-source-tanks-tracks-and-n-wheeled-vehicles
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
	float TrackMaxDrivingForce = 45000000.0;
	UTankTrack();
	/// assume 40 Ton tank and 0-60 in 10 seconds. F=ma
private:

	FVector ForceApplied;
	void DriveTrack(float CurrentThrottle);
	float CurrentThrottle = 0.0;
	TArray<ASprungWheel*> GetWheels() const;

};
