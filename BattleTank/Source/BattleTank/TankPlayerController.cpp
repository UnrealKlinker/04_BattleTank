// Copyright Paul Klinker, 2019.

#include "TankPlayerController.h"
#include "Engine/World.h"


// Start the game
void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("Player controller cannot find Tank Aiming Component at BeginPlay"));
		return;
	}
	FoundAimingComponent(TankAimingComponent);
}

	// Aim towards crosshair
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController Tick"));

	// Aim towards crosshair
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) // e.g. if not possessing
	{
		return;
	}
	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("Player controller cannot find Tank Aiming Component ay"));
		return;
	}

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) //Has "side-effect" - it line traces
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
		// get world location if linetrace through crosshair
		TankAimingComponent->AimAt(HitLocation);
		// If it hits the landscape
			//TODO Tell the controlled tank to aim at this point
	}
}

//Get world location of linetrace through crosshair, true if i
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	
	// From instructor: Find the crosshair projection
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	// de-project the screen position of the crosshair to a world direction
	FVector2D ScreenLocation = FVector2D(CrossHairXLocation*ViewportSizeX, CrossHairYLocation*ViewportSizeY);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// line-trace along that look direction and see what we hit (up to max range)
		///UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *LookDirection.ToString());
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	// My notes: if hit, return true and set the HitLocation value
	// draw a line from gun barrel through dot to infinity
	// get actors that intersect line by checking points within a volume.
	return false;
}

// Get the direction the reticle is facing
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // unneeded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
		// calculate the reach

	auto StartLocation = PlayerCameraManager->GetCameraLocation();


	FVector RotatorVector = LookDirection*LineTraceRange;
	FVector LineTraceEnd = StartLocation + RotatorVector;
	FHitResult ObjectHit;
	if (GetWorld()->LineTraceSingleByChannel(
		OUT ObjectHit, 
		StartLocation, 
		LineTraceEnd, 
		ECollisionChannel::ECC_Visibility)) //line trace succeeds
		{
			//set hit location
			HitLocation = ObjectHit.Location;
			return true;
		}
		return false; // line trace didn't succeed
//	UE_LOG(LogTemp, Warning, TEXT("Line trace end: %s"), *LineTraceEnd.ToString());
	

}




