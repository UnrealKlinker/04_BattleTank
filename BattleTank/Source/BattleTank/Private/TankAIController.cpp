// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

// Get the player controlled tank
ATank* ATankAIController::GetControlledTank() const
{
	auto *TheTank = Cast<ATank>(GetPawn());
	if (TheTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController controlled tank: %s"), *(TheTank->GetName()));

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController pawn not possessing a tank."));

	}
	return TheTank;
}

// Start the game
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AI Tank Controller Begin Play"));
	ATank* TheTank = GetControlledTank();
}