// Copyright Paul Klinker, 2019.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.h"
#include "SpawnPoint.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	AActor* GetGeneratedActor() const;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Setup") /// this make it editable on the blueprint only
	TSubclassOf<AActor> SpawnClass;

	UPROPERTY() // A UPROPERTY so garbage collector can track.
	AActor *SpawnPointActor;

};
