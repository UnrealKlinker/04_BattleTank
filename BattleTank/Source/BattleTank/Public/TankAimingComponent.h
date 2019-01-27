// Copyright Paul Klinker, 2019.

#pragma once

#include "CoreMinimal.h"
#include "Math/Vector.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

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
	UFUNCTION(BlueprintCallable)
		void Fire();

	void AimAt(FVector TargetLocation);

	/**
	* Called when the game starts or when spawned. Will reset the fire time to prevent immediate firing.
	*/
	virtual void BeginPlay() override;

	/**
	 * Function called every frame on this UTankAimingComponent.
	 *
	 * @param DeltaTime - The time since the last tick.
	 * @param TickType - The kind of tick this is, for example, are we paused, or 'simulating' in the editor
	 * @param ThisTickFunction - Internal tick function struct that caused this to run
	 */
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();

	EFiringStatus GetFiringStatus() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup") /// this make it editable on the blueprint only
		TSubclassOf<AProjectile> ProjectileBlueprint; // consider https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringStatus = EFiringStatus::EFS_Reloading;

	//TODO Find reasonable default for cannon velocity
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 100000; // speed in cm/s
	UPROPERTY(EditAnywhere, Category = "Firing")
		float ReloadTimeInSeconds = 3; //Time to reload the cannon in seconds

private:
	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;
	double LastFireTime = 0.0;
	FVector LastBarrelPosition;

};