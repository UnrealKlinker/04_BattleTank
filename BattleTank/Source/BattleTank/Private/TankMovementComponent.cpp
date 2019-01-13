// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankMovementComponent.h"
#include "../Public/TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
	{
		return;
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}
void UTankMovementComponent::IntendTurnRight(float Throw)
{
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}
void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward %f"), Throw);
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);

}