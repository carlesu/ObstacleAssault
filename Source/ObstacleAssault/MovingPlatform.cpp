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
	/*
	// Rotate platform
		// Get current rotation
	auto CurrentRotation = GetActorRotation();
		// Add a vector to that rotation
	CurrentRotation += RotationVelocity * DeltaTime;
		// Set the rotation
	SetActorRotation(CurrentRotation);
	UE_LOG(LogTemp, Display, TEXT("(%s) Rotate platform, to %f,%f,%f deg , dT %f s"), *GetName(), CurrentRotation.Roll, CurrentRotation.Pitch, CurrentRotation.Yaw, DeltaTime);
	*/

	/*
	https://forums.unrealengine.com/t/issues-with-rotation-at-180-degrees/90113
	https://docs.unrealengine.com/5.1/en-US/API/Runtime/Engine/GameFramework/AActor/SetActorRotation/
	https://stackoverflow.com/questions/70702703/is-there-a-way-to-rotate-an-actors-pitch-past-90-degrees-in-unreal-engine-4


	It is important to note that "SetActorRotation" has Compile Time Polymorphism, hence it is overloaded
	bool SetActorRotation (FRotator NewRotation, ETeleportType Teleport)
	bool SetActorRotation (const FQuat& NewRotation, ETeleportType Teleport)

	Working with Euler angles come with it's limitations. We shall use Quaternions.
	We could work out this on this way https://forums.unrealengine.com/t/rotate-a-mesh-around-its-center-using-quaternion/444575
	But it is easier to use the AddActorLocalRotation function, which is a wrapper for AddActorWorldRotation.
	*/

	/* Not working
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation += RotationVelocity * DeltaTime;
	SetActorRotation(CurrentRotation.Quaternion());
	*/

	/* Not working
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation += RotationVelocity * DeltaTime;
	FQuat NewRotation = FQuat::MakeFromEuler(CurrentRotation.Euler());
	SetActorRotation(NewRotation);
	*/

	/* Not working
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation += RotationVelocity * DeltaTime;
	CurrentRotation.Normalize();
	SetActorRotation(CurrentRotation);
	*/

	/* Not working
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation += RotationVelocity * DeltaTime;
	SetActorRotation(CurrentRotation.GetEquivalentRotator());
	*/
		

	// In the case of Yaw it is true that changes from 180 to -180, but I see no real problem with that
	// Also the pitch value is always between -90 and 90, the thing is that when Pitch reaches 90, suddenly changes from 0, 90, 0, to 180, 90, 180; and goes nuts
	// To avoid the edge cases, The solution is to use AddActorLocalRotation and pass in the delta instead (RotationVelocity * DeltaTime)
	auto deltaRotation = RotationVelocity * DeltaTime;
	AddActorLocalRotation(deltaRotation);
	FRotator CurrentRotation = GetActorRotation();
	UE_LOG(LogTemp, Display, TEXT("(%s) Rotate platform, to %f,%f,%f deg , dT %f s"), *GetName(), CurrentRotation.Roll, CurrentRotation.Pitch, CurrentRotation.Yaw, DeltaTime);
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