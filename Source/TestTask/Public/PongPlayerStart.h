// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "PongPlayerStart.generated.h"

class APongGoalZone;

/**
 * 
 */
UCLASS()
class TESTTASK_API APongPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:

	bool IsPossessed();
	void Free();
	void Claim(APlayerController* PlayerController);
	ACameraActor* GetCamera();
	APongGoalZone* GetGoalZone();
protected:
	AController* OwningPlayer;
	UPROPERTY(EditInstanceOnly)
	ACameraActor* OwningCamera;
	UPROPERTY(EditInstanceOnly)
	APongGoalZone* GoalZone;
};