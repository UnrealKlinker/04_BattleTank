// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
// Get the player controlled tank
ATank* ATankPlayerController::GetControlledTank() const
{
	auto *TheTank = Cast<ATank>(GetPawn());
	if (TheTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController controlled tank: %s"), *(TheTank->GetName()));

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController pawn not possessing a tank."));
	}
	return TheTank;
}

// Start the game
void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
	ATank* TheTank = GetControlledTank();
}

	// Aim towards crosshair
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Tick"));

	// Aim towards crosshair
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) //Has "side-effect" - it line traces
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// get world location if linetrace through crosshair
		// If it hits the landscape
			//TODO Tell the controlled tank to aim at this point
	}
}

//Get world location of linetrace through crosshair, true if i
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	//ATank* TheTank = GetControlledTank();
	//TheTank->GetComponentsByTag
	//GetWorld()->GetGameViewport()->
	HitLocation = FVector(1.0);
	// if hit, return true and set the HitLocation value
	// draw a line from gun barrel through dot to infinity
	// get actors that intersect line by checking points within a volume.
	return true;
}

