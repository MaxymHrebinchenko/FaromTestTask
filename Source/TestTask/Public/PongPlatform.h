// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputMappingContext.h"
#include "PongPlatform.generated.h"

class UPongMappingContext;

UCLASS()
class TESTTASK_API APongPlatform : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APongPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
