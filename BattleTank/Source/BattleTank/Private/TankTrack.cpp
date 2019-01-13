// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Throttle value %f for track %s"), Throttle, *Name);
	//TODO clamp the throttle to the range
	/// getting forward vector of the track
	
	auto ForceApplied = GetForwardVector() * Throttle*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	UPrimitiveComponent *TankRoot = Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


