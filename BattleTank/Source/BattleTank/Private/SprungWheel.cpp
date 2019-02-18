// Copyright Paul Klinker, 2019.

#include "SprungWheel.h"
//#include "Tank.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(Spring);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Spring);
	
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	// gets the parent actor
	if (GetAttachParentActor())
	{
		UPrimitiveComponent *BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (!BodyRoot)
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't find body root."));
			return;
		}
		
	//AttachToComponent
//	Spring->SetConstrainedComponents((UPrimitiveComponent)GetDefaultAttachComponent(), NAME_None, Wheel, NAME_None);
	Spring->SetConstrainedComponents(BodyRoot, NAME_None, Wheel, NAME_None);
	}

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

