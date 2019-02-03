// Copyright Paul Klinker, 2019.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/TankAimingComponent.h"
#include "TankPlayerController.generated.h" // must be last include


/// forward declarations
//class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

protected:
	// Start the tank moving the barrel so the shot would hit where the crosshair intersects the world.
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector & HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f; // distance in cm

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()  // Must be a UFUNCTION to get called when tank is destroyed.
		void OnPlayerDeath();

};
