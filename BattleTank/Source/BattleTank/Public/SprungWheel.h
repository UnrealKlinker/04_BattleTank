// Copyright Paul Klinker, 2019.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// adds a positive force to drive the wheel forward and a negative force for reverse
	void AddDrivingForce(float ForceMagnitude);
	// adds a positive force to drive the wheel forward and a negative force for reverse
	void AddDrivingForce(FVector Force);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent *Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent *Axle = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent *AxleWheelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent *Spring = nullptr;

};
