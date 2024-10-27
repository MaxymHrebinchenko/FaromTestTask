// Fill out your copyright notice in the Description page of Project Settings.
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, text)

#include "PongPlayerController.h"
#include "Engine/TriggerBox.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "PongGoalZone.h"
#include "PongPlatform.h"

#include <InputAction.h>
#include "PongMappingContext.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <Net/UnrealNetwork.h>
#include <Net/Core/PushModel/PushModel.h>

APongPlayerController::APongPlayerController()
{
	PlatformSpeed = 75;
	Context = NewObject<UPongMappingContext>();
	Context->SetSpeed(PlatformSpeed);

	bAutoManageActiveCameraTarget = false;
}

void APongPlayerController::IncreaseScore()
{
	if (HasAuthority())
	{
		MyScore += 1;
		MARK_PROPERTY_DIRTY_FROM_NAME(APongPlayerController, MyScore, this);
		//print(GetName() + ": Score increased. Now: " + FString::FromInt(Score));
	}
}

void APongPlayerController::IncreaseEnemyScore()
{
	if (HasAuthority())
	{
		EnemyScore += 1;
		MARK_PROPERTY_DIRTY_FROM_NAME(APongPlayerController, EnemyScore, this);
		//print(GetName() + ": Score increased. Now: " + FString::FromInt(Score));
	}
}

FOnReadyEvent& APongPlayerController::GetOnReadyEvent()
{
	return OnReadyEvent;
}

void APongPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(APongPlayerController, MyScore, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(APongPlayerController, EnemyScore, SharedParams);
}

void APongPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	NotifyServer();
}

void APongPlayerController::ClientSetCamera_Implementation(ACameraActor* Camera)
{
	if (HasAuthority())
	{
		ClientSetCamera(Camera);
	}
	else
	{
		if (Camera == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("MulticastInitializeSpawn_Implementation: Camera wasn't set"));
			return;
		}

		if (Camera)
		{
			CameraActor = Camera;
			SetViewTarget(Camera);
			bAutoManageActiveCameraTarget = false;
		}
	}
}



void APongPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void APongPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void APongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (Context)
			{
				InputSystem->AddMappingContext(Context, 0);

				UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
				FEnhancedActionKeyMapping mapping = Context->GetMapping(0);
				Input->BindAction(mapping.Action, ETriggerEvent::Triggered, this, &APongPlayerController::MovementCallback);
			}
		}
	}
}

void APongPlayerController::OnRep_UpdateScore()
{
	UpdateUIScore.Broadcast(MyScore, EnemyScore);
}

void APongPlayerController::ServerMovement_Implementation(const float Speed)
{
	if (HasAuthority())
	{
		
		float Movement = Speed;
		auto ControlledPawn = GetPawn();
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		FVector Right = ControlledPawn->GetActorRightVector();
		if (ControlledPawn)
		{
			ControlledPawn->AddActorWorldOffset(DeltaTime * Movement * Right, true);
		}
	}
	else
	{
		ServerMovement(Speed);
	}
}

void APongPlayerController::NotifyServer_Implementation()
{
	if (HasAuthority())
		OnReadyEvent.ExecuteIfBound(this);
	else
		NotifyServer();
}

void APongPlayerController::MovementCallback(const FInputActionInstance& Instance)
{
	ServerMovement(Instance.GetValue().Get<float>());
}