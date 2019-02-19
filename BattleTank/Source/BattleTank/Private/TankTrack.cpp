// Copyright Paul Klinker, 2019.

#include "../Public/TankTrack.h"
#include "../Public/SprungWheel.h"
#include "../Public/SpawnPoint.h"
/**
* Constructor
*/
UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

/**
* Sets how fast the tank will move.
*/
void UTankTrack::SetThrottle(float Throttle)
{
	if (Throttle == 0.0)
	{
		return;
	}
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	//TODO clamp the throttle to the range
	/// getting forward vector of the track
	//	ForceApplied = GetForwardVector() * CurrentThrottle*TrackMaxDrivingForce;
	TArray<ASprungWheel*> Wheels = GetWheels();
//	auto ForcePerWheel = ForceApplied / Wheels.Num();
	UE_LOG(LogTemp, Warning, TEXT("CurrentThrottle - %f"), CurrentThrottle);
	auto  ForcePerWheel = CurrentThrottle * TrackMaxDrivingForce/ Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(TrackMaxDrivingForce, ForcePerWheel);
	}
	
	/// auto Name = GetName();
	/// UE_LOG(LogTemp, Warning, TEXT("Throttle set to: %s"), *ForceApplied.ToString());

}


// Returns all the wheels by finding them in the children components
TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray <ASprungWheel *> Wheels;
	TArray <USceneComponent *> ChildComponents;
	GetChildrenComponents(true, ChildComponents);

	for (USceneComponent* ChildComponent : ChildComponents)
	{
		USpawnPoint *Child = Cast<USpawnPoint>(ChildComponent);
		if (!Child) continue;
		AActor *GeneratedChild = Child->GetGeneratedActor();
		auto SprungWheel = Cast<ASprungWheel>(GeneratedChild);
		if (!SprungWheel) continue;
		Wheels.Add(SprungWheel);
	}
	return Wheels;
}