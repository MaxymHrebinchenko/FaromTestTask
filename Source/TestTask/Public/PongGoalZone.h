// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "PongGoalZone.generated.h"

class APongPlayerController;
DECLARE_DELEGATE_OneParam(FOnGoalEvent, APongPlayerController*);



UCLASS()
class TESTTASK_API APongGoalZone : public ATriggerBox
{
	GENERATED_BODY()
public:
	void SetOwnerPlatform(APongPlayerController* PlayerController);
	void FreeOwnerPlatform();
	void PostInitializeComponents() override;
protected:
	APongPlayerController* OwnerPlatform;

	//TDelegate<void(APlayerController*)>
	FOnGoalEvent OnGoalEvent;
	
	UFUNCTION()
	void OnGoalOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FOnGoalEvent& GetOnGoalEvent();
};


