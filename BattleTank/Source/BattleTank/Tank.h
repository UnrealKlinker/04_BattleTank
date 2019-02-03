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
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 HitPoints = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth = HitPoints;
};
