// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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
	ATank *ThisTank = Cast<ATank>(GetPawn());
	ATank *PlayerTank = nullptr;
	APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerTank = Cast<ATank>(PlayerController->GetPawn());
	}
	else {
		/// UE_LOG(LogTemp, Warning, TEXT("Can't find player tank."));
		return;
	}

	if (ThisTank && PlayerTank)
	{
		// TODO Move towards the player
		// Aim towards the player
		ThisTank->AimAt(PlayerTank->GetActorLocation());
		// Fire every frame 
		ThisTank->Fire();
	}
}