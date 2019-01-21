// Copyright Paul Klinker, 2019.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "TankAIController.generated.h" // must be last

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	// How close can the AI tank get to the player in cm
	float AcceptanceRadius = 3000; 
};
