// Copyright Paul Klinker, 2019.

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
	if (ensure(PlayerController))
	{
		PlayerTank = Cast<ATank>(PlayerController->GetPawn());
	}
	else {
		/// UE_LOG(LogTemp, Warning, TEXT("Can't find player tank."));
		return;
	}

	if (ensure(ThisTank && PlayerTank))
	{
		// TODO Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius, true, true, false);
		// Aim towards the player
		ThisTank->AimAt(PlayerTank->GetActorLocation());
		// Fire every frame 
		ThisTank->Fire();
	}
}