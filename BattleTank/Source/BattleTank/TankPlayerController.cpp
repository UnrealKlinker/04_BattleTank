// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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

