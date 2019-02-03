// Copyright Paul Klinker, 2019.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}


float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: DamageToApply: %i, DamageAmount: %f, CurrentHealth: %i"), Time, DamageToApply, DamageAmount, CurrentHealth);

	return DamageToApply;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

