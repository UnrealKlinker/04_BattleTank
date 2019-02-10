// Copyright Paul Klinker, 2019.

#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(Spring);

	ShockAbsorber = CreateDefaultSubobject<UStaticMeshComponent>(FName("Shock Absorber"));
	if (!ensure(ShockAbsorber))
	{
		UE_LOG(LogTemp, Warning, TEXT("ShockAbsorber Collsion Mesh can't be created."));
		return;
	}
	Spring->SetupAttachment(ShockAbsorber);
	Spring->SetConstrainedComponents(ShockAbsorber, FName("ShockAbsorber"), Wheel, FName("Wheel"));

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(ShockAbsorber);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	//ATank TheTank = GetAttachParentActor(); gets the tank
	//AttachToComponent
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

