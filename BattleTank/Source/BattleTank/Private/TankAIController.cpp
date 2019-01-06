// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Get the player controlled tank
ATank* ATankAIController::GetControlledTank() const
{
	auto *ThisTank = Cast<ATank>(GetPawn());
	UE_LOG(LogTemp, Warning, TEXT("Found AI tank %s."), *(ThisTank->GetName()));
	return ThisTank;
}

ATank * ATankAIController::GetPlayerTank() const
{
	ATank *TheTank = nullptr;
	APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		TheTank = Cast<ATank>(PlayerController->GetPawn());
		/// UE_LOG(LogTemp, Warning, TEXT("Found player tank %s."), *(TheTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Can't find player tank."));
	}
	return TheTank;
}

// Start the game
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	///UE_LOG(LogTemp, Warning, TEXT("AI Tank Controller Begin Play"));
}

// Tick Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank* ThisTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();
	if (ThisTank && PlayerTank)
	{
		// TODO Move towards the player
		// Aim towards the player
		ThisTank->AimAt(PlayerTank->GetActorLocation());
		// Fire if ready
	}
}