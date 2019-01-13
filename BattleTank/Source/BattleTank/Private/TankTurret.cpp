// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankTurret.h"
#include "Math/UnrealMathUtility.h"


// Called when the game starts or when spawned
void UTankTurret::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewRotation = RelativeRotation.Yaw + RotationChange;
	
	
	FRotator NewRelativeRotation = FRotator(RelativeRotation.Pitch, NewRotation, RelativeRotation.Roll);
	// auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f Aim solution found %f turret rotation"), Time,  NewRotation);
	SetRelativeRotation(NewRelativeRotation, 0, 0);
}

