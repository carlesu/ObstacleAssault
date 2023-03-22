// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// UPROPERTY(EditAnywhere)
	// FVector MyVector = FVector(-13850.0, -2700.0, 4055.15);

	int m_ticker{0};
	float m_multiplier{1};

	// New approach
	UPROPERTY(EditAnywhere, Category="CUbach Category")
	FVector PlatformVelocity = FVector(500, 0, 0);

	// Only cpp property
	FVector StartLocation;

	UPROPERTY(VisibleAnywhere, Category="CUbach Category")
	double DistanceMoved{0};   // Distance we currently moved
	UPROPERTY(EditAnywhere, Category="CUbach Category")
	double MoveDistance{500};  // Maximum move distance

	void MovePlatform(float DeltaTime);

	void RotatePlatform(float DeltaTime);

	bool ShouldPlatformReturn();
};
