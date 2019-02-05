// Copyright Paul Klinker, 2019.

#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

// Start the game
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	// Register for death event
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

	if (ensure(ThisTank))
	{
		if (PlayerTank) { // don't ensure here because the PlayerTank will be null once it is destroyed.
			// TODO Move towards the player
			MoveToActor(PlayerTank, AcceptanceRadius, true, true, false);
			auto TankAimingComponent = ThisTank->FindComponentByClass<UTankAimingComponent>();
			// Aim towards the player
			TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

			// If locked then fire
			if (TankAimingComponent->GetFiringStatus() == EFiringStatus::EFS_Locked)
			{
				TankAimingComponent->Fire();
			}
		}
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);

	}
}

// AI tank received death call.
void ATankAIController::OnPossessedTankDeath() {
	UE_LOG(LogTemp, Warning, TEXT("AI tank received death call."));
	GetPawn()->DetachFromControllerPendingDestroy();
}
