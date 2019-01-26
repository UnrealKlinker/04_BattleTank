// Copyright Paul Klinker, 2019.

#include "../Public/TankTrack.h"

/**
* Constructor
*/
UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Start the game
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("TankTrack hit ground."));
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
// calculate the slippage speed - moving sideways. IF no slippage it will be 0, if moving entirely sideways it will be the speed
	//FVector ForwardVector = GetForwardVector();
	//auto ForwardIntention = ForceApplied.GetSafeNormal();
	//float SlippageSpeed = FVector::DotProduct(ForwardIntention, ForwardVector);
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	
	// work out the required acceleration and put in opposite direction
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime) *GetRightVector(); 
	// calculate and apply the sideways for F=ma and divide by two because there are two tracks
	UStaticMeshComponent *TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass()*CorrectionAcceleration)/2;
	TankRoot->AddForce(CorrectionForce);
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
	//TODO clamp the throttle to the range
	/// getting forward vector of the track
	
	ForceApplied = GetForwardVector() * Throttle*TrackMaxDrivingForce;
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


