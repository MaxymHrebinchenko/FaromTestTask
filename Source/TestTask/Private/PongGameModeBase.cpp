// Fill out your copyright notice in the Description page of Project Settings.
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, text)


#include "PongGameModeBase.h"
#include "EngineUtils.h"
#include "PongPlayerStart.h"
#include "PongPlayerController.h"
#include "Camera/CameraActor.h"
#include "PongGoalZone.h"
#include "PongBall.h"
#include "Kismet/GameplayStatics.h"
#include "PongPlatform.h"

void APongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	AddPlayer(NewPlayer);
	InitializePongPlayer(NewPlayer);

	Super::PostLogin(NewPlayer);
}

void APongGameModeBase::Logout(AController* Exiting)
{
	if (auto PlayerController = Cast<APlayerController>(Exiting))
	{
		Players.Remove(PlayerController);
		if (ReadyPlayers.Find(PlayerController) != INDEX_NONE)
		{
			ReadyPlayers.Remove(PlayerController);
			APongBall* Ball = Cast<APongBall>(UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass()));
			Ball->ResetBall();
			Ball->SetActorTickEnabled(false);
		}
	}Super::Logout(Exiting);
}

void APongGameModeBase::ActivateAndResetBall()
{
	APongBall* Ball = Cast<APongBall>(UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass()));
	Ball->ResetBall();
	Ball->SetRandomAngle();
	Ball->SetActorTickEnabled(true);
}

void APongGameModeBase::InitializePongPlayer(APlayerController* NewPlayer)
{
	auto PlayerStart = GetPlayerStartWithTag();

	if (PlayerStart == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PostLogin: GetPlayerStartWithTag returned nullptr"));
	}

	PlayerStart->Claim(NewPlayer);
	NewPlayer->StartSpot = PlayerStart;

	if (auto PongController = Cast<APongPlayerController>(NewPlayer))
	{
		PongController->ClientSetCamera(PlayerStart->GetCamera());
		if (auto GoalZone = PlayerStart->GetGoalZone())
			GoalZone->SetOwnerPlatform(PongController);
		else
			UE_LOG(LogTemp, Error, TEXT("GoalZone for PlayerStart is nullptr"));

		PongController->GetOnReadyEvent().BindLambda([this](APlayerController* Controller) {
			if (Controller->GetPawn()->GetClass()->IsChildOf(APongPlatform::StaticClass()))
			{
				//print("ReceivedNotify of APongPlatform");
				ReadyPlayers.AddUnique(Controller);
				if (ReadyPlayers.Num() == 2)
				{
					GetWorld()->GetTimerManager().SetTimer(
						FBallResetDelay,
						this,
						&APongGameModeBase::ActivateAndResetBall,
						2,
						false
					);
				}
			}
			else
			{
				//print("ReceivedNotify of " + Controller->GetPawn()->GetName());
				ReadyPlayers.Remove(Controller);
			}
			});

		APongGoalZone* Zone = PlayerStart->GetGoalZone();
		Zone->GetOnGoalEvent().BindLambda([this](APongPlayerController* OwnerController) {
			for (auto* Object : Players)
			{
				if (OwnerController == Object)
				{
					OwnerController->IncreaseEnemyScore();
					continue;
				}
				Cast<APongPlayerController>(Object)->IncreaseScore();
			}
			auto* Ball = UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass());
			Ball->SetActorTickEnabled(false);
			GetWorld()->GetTimerManager().SetTimer(
				FBallResetDelay,
				this,
				&APongGameModeBase::ActivateAndResetBall,
				2,
				false
			);
		});
	}
}

void APongGameModeBase::AddPlayer(APlayerController* PlayerController)
{
	Players.AddUnique(PlayerController);
	return;
}

APongPlayerStart* APongGameModeBase::GetPlayerStartWithTag()
{
	for (TActorIterator<APongPlayerStart> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		APongPlayerStart* Start = *Iterator;
		if (!Start->PlayerStartTag.IsNone() && !Start->IsPossessed())
		{
			return Start;
		}
	}
	return nullptr;
}
