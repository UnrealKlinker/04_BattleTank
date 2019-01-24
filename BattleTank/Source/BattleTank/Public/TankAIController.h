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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTankAimingComponent* TankAimingComponent = nullptr;
//	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
//	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	// How close can the AI tank get to the player in cm
	float AcceptanceRadius = 3000; 

};
