// Copyright Paul Klinker, 2019.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // must be last include

// forward declarations
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelReference(UTankBarrel *BarrelToSet);
	UFUNCTION(BlueprintCallable)
	void Fire();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Firing")
	//TODO Find reasonable default for cannon velocity
	float LaunchSpeed = 100000; // speed in cm/s

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 3; //Time to reload the cannon in seconds
	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup") /// this make it editable on the blueprint only
	TSubclassOf<AProjectile> ProjectileBlueprint; // consider https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf

	// Local barrel reference
	UTankBarrel* Barrel = nullptr; //TODO Remove
};
