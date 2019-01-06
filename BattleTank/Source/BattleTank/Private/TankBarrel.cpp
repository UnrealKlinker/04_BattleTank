// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	// Turn the turret and then elevate or depress the barrel based on a max elevation speed and frame time
	// Use the blueprint to contrl the speed of the move - frame independent
	UE_LOG(LogTemp, Warning, TEXT("%f: Barrel elevation: %f"), Time, RelativeSpeed);
}