// Copyright Paul Klinker, 2019.

#include "../Public/TankMovementComponent.h"
#include "../Public/TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	/// replacing functionality so don't call super
	auto TankName = GetOwner()->GetName();
	/// the direction the AI wants to move the tank
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	/// direction the tank is facing
	auto TankForward = GetOwner()->GetActorForwardVector();
	/// use the cosine function to get the tank to move in the AI direction - via the vector dot product
	float DotProduct = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveForward(DotProduct);

	// use the sine function to get the amount the tank must turn to face the player - via the cross product so order matters
	FVector TankTurn = FVector::CrossProduct(TankForward, AIForwardIntention);
	IntendTurnRight(TankTurn.Z);

	///UE_LOG(LogTemp, Warning, TEXT("Tank %s is moving at velocity %s"), *TankName,*MoveVelocityString);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
	{
		return;
	}
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward %f"), Throw);
	Throw = FMath::Clamp<float>(Throw, -1, +1);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}
void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
	{
		return;
	}
	Throw = Throw * TrackTurnForceMultiplier;
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);

}
void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
	{
		return;
	}
	Throw = Throw * TrackTurnForceMultiplier;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}