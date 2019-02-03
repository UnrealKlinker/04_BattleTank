// Copyright Paul Klinker, 2019.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h" // must be last

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTankAimingComponent* TankAimingComponent = nullptr;
//	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
//	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	// How close can the AI tank get to the player in cm

	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 3000; 

private: 
	virtual void SetPawn(APawn* InPawn) override; // this gets called when the pawn is possessed.
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()  // Must be a UFUNCTION to get called when tank is destroyed.
		void OnPossessedTankDeath();

};
