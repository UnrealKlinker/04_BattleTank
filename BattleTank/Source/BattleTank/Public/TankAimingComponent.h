// Copyright Paul Klinker, 2019.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel;
class UTankTurret;
class UActorComponent;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EFiringStatus : uint8
{
	EFS_Reloading UMETA(DisplayName = "Reloading"),
	EFS_Aiming 	UMETA(DisplayName = "Aiming"),
	EFS_Locked	UMETA(DisplayName = "Locked")
};

// Used to aim the tank's cannon
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void AimAt(FVector TargetLocation, float LaunchSpeed) const;
	UFUNCTION(BlueprintCallable, Category = "Input")
	void AimBarrelTowards(FVector AimDirection) const;
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);


protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::EFS_Aiming;

private:
	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;

};
