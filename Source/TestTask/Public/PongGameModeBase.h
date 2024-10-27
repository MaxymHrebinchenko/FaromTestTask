// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameModeBase.generated.h"

class APongPlayerStart;

/**
 * 
 */
UCLASS()
class TESTTASK_API APongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void PostLogin(APlayerController* NewPlayer) override;
	void Logout(AController* Exiting) override;
	void ActivateAndResetBall();
protected:

	void InitializePongPlayer(APlayerController* NewPlayer);
	void AddPlayer(APlayerController* PlayerController);

	APongPlayerStart* GetPlayerStartWithTag();
	
	TArray<APlayerController*> Players;
	TArray<APlayerController*> ReadyPlayers;
	FTimerHandle FBallResetDelay;
};
