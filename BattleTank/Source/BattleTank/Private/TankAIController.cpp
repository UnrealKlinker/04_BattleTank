// Copyright Paul Klinker, 2019.

#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Start the game
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
/*	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("AI controller cannot find Tank Aiming Component at BeginPlay"));
		return;
	}
	FoundAimingComponent(TankAimingComponent);
	*/
}

// Tick Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto *ThisTank = GetPawn();
	APawn *PlayerTank = nullptr;
	APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
	if (ensure(PlayerController))
	{
		PlayerTank = PlayerController->GetPawn();
	}
	else {
		/// UE_LOG(LogTemp, Warning, TEXT("Can't find player tank."));
		return;
	}

	if (ensure(ThisTank && PlayerTank))
	{
		// TODO Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius, true, true, false);
		auto TankAimingComponent = ThisTank->FindComponentByClass<UTankAimingComponent>();
		// Aim towards the player
		TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

		// Fire every frame 
		//TODO fix this
		//ThisTank->Fire();
	}
}
