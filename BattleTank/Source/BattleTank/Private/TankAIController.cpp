// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Get the player controlled tank
ATank* ATankAIController::GetControlledTank() const
{
	auto *ThisTank = Cast<ATank>(GetPawn());
	if (ThisTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController controlled tank: %s"), *(ThisTank->GetName()));

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController pawn not possessing a tank."));

	}
	return ThisTank;
}

ATank * ATankAIController::GetPlayerTank() const
{
	ATank *TheTank = nullptr;
	APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		TheTank = Cast<ATank>(PlayerController->GetPawn());
		UE_LOG(LogTemp, Warning, TEXT("Found player tank %s."), *(TheTank->GetName()));
	}
	return TheTank;
}

// Start the game
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AI Tank Controller Begin Play"));
	ATank* ThisTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();
}

// Tick Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}