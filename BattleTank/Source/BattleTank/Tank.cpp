// Copyright Paul Klinker, 2019.

#include "Tank.h"
#include "Public/TankBarrel.h"


// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

}



void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

