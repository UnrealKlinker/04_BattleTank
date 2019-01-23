// Copyright Paul Klinker, 2019.

#include "../Public/TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	if (Throttle == 0.0)
	{
		return;
	}
	//TODO clamp the throttle to the range
	/// getting forward vector of the track
	
	auto ForceApplied = GetForwardVector() * Throttle*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	UPrimitiveComponent *TankRoot = Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent());
	if (!ensure(TankRoot))
	{
		return;
	}

	/// auto Name = GetName();
	/// UE_LOG(LogTemp, Warning, TEXT("Throttle set to: %s"), *ForceApplied.ToString());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


