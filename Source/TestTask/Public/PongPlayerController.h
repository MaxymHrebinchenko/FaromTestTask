// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "PongPlayerController.generated.h"

struct FInputActionInstance;
class APongGoalZone;
class UPongMappingContext;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateUIScore,int32, MyScore, int32, EnemyScore);
DECLARE_DELEGATE_OneParam(FOnReadyEvent,APlayerController*);

UCLASS()
class TESTTASK_API APongPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	APongPlayerController();

	UFUNCTION(Client, Reliable)
	void ClientSetCamera(ACameraActor* Camera);

	void IncreaseScore();
	void IncreaseEnemyScore();
	FOnReadyEvent& GetOnReadyEvent();

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	void OnRep_Pawn() override;
protected:
	ACameraActor* CameraActor;
	UPongMappingContext* Context;
	FOnReadyEvent OnReadyEvent;
	UPROPERTY(BlueprintAssignable)
	FUpdateUIScore UpdateUIScore;
	UPROPERTY(ReplicatedUsing = OnRep_UpdateScore)
	int32 MyScore;
	UPROPERTY(ReplicatedUsing = OnRep_UpdateScore)
	int32 EnemyScore;
	
	void BeginPlay() override;
	void OnPossess(APawn* aPawn) override;

	UFUNCTION(Server, Reliable)
	void ServerMovement(const float Speed);
	UFUNCTION(Server, Reliable)
	void NotifyServer();
	void MovementCallback(const FInputActionInstance& Instance);
	void SetupInputComponent() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float PlatformSpeed;

	UFUNCTION()
	void OnRep_UpdateScore();
	
};
