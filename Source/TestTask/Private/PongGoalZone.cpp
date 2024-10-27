// Fill out your copyright notice in the Description page of Project Settings.
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, text)


#include "PongGoalZone.h"
#include "Components/ShapeComponent.h"
void APongGoalZone::SetOwnerPlatform(APongPlayerController * PlayerController)
{
	OwnerPlatform = PlayerController;
}

void APongGoalZone::FreeOwnerPlatform()
{
	OwnerPlatform = nullptr;
}

void APongGoalZone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorBeginOverlap.AddDynamic(this, &APongGoalZone::OnGoalOverlap);
}

void APongGoalZone::OnGoalOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	OnGoalEvent.ExecuteIfBound(OwnerPlatform);
}

FOnGoalEvent& APongGoalZone::GetOnGoalEvent()
{
	return OnGoalEvent;
}
