// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// SetActorLocation(MyVector);

	// Get the start location
	StartLocation = GetActorLocation();

	// All Spawned
	
	UE_LOG(LogTemp, Display, TEXT("All Spawned: %f // %s"), MoveDistance, *Super::GetName());
	UE_LOG(LogTemp, Warning, TEXT("All Spawned: %f // %s"), MoveDistance, *Super::GetName());
	UE_LOG(LogTemp, Error, TEXT("All Spawned: %f // %s"), MoveDistance, *Super::GetName());

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
	
}


void AMovingPlatform::MovePlatform(float DeltaTime)
{
	
	
		
	if (ShouldPlatformReturn()) {
		// Reverse direction of motion if gone too far
		float OverShoot = DistanceMoved - MoveDistance;
		UE_LOG(LogTemp, Display, TEXT("(%s) Overshoot distance calculated = %f"), *Super::GetName(), OverShoot);
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		// StartLocation = CurrentLocation; // This can cause overshoot depoending on dt
		// To avoid overshoot, we calculate the poasition if we moved the exact distance we want, otherwise if it's 
		// too fast we can cause overshoot and DistanceMoved > MoveDistance, and we set the current location bigger 
		// than MoveDistance, making a displacement each time.
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = - PlatformVelocity;

	}
	else
	{
		// Move platform forwards
			// Get current location
		auto CurrentLocation = GetActorLocation();
			// Add a vector to that location
		CurrentLocation += PlatformVelocity * DeltaTime;
			// Set the location
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{	
	UE_LOG(LogTemp, Display, TEXT("(%s) Rotate platform, %f"), *GetName(), DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{	
	// Send platform back if gone too far
		// Check how far we've moved
	return GetDistanceMoved() >= MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{	
	return FVector::Dist(StartLocation, GetActorLocation());  // Do not mind the order
}