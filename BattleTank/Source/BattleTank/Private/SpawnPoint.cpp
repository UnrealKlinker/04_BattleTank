// Copyright Paul Klinker, 2019.

#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	auto NewActor = GetWorld()->SpawnActorDeferred<AActor>(*SpawnClass, GetComponentTransform());
	if (!ensure(NewActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("USpawnPoint new actor is missing."));
		return;
	}
	NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(NewActor, GetComponentTransform());

	// ...
	
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

