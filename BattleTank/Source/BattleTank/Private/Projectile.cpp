// Copyright Paul Klinker, 2019.

#include "../Public/Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CannonProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Cannon Projectile Movement"));
	CannonProjectileMovement->bAutoActivate = false;

}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	auto Time = GetWorld()->GetTimeSeconds(); 
	///UE_LOG(LogTemp, Warning, TEXT("%f Firing cannon at speed %f."), Time, LaunchSpeed);
	CannonProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector*LaunchSpeed);
	CannonProjectileMovement->Activate();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

