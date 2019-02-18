// Copyright Paul Klinker, 2019.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;



/**
 * Used to move the tank with fly by wire by driving the tank tracks.
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw); // Throw is how far forward or back the stick is
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);
    UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnLeft(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet);

	/** path following: request new velocity */
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack *LeftTrack = nullptr;
	UTankTrack *RightTrack = nullptr;
};
