// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongBall.generated.h"

UCLASS()
class TESTTASK_API APongBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APongBall();

	void ResetBall();
	void SetRandomAngle();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float AngleRange = 35;
	float Speed = 1000;
	FVector StartPos;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
