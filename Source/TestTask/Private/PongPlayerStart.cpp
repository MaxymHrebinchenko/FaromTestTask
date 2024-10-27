// Fill out your copyright notice in the Description page of Project Settings.


#include "PongPlayerStart.h"
#include "PongGoalZone.h"

bool APongPlayerStart::IsPossessed()
{
	return OwningPlayer?true:false;
}

void APongPlayerStart::Free()
{
	OwningPlayer = nullptr;
	OwningCamera = nullptr;
}

void APongPlayerStart::Claim(APlayerController* PlayerController)
{
	OwningPlayer = PlayerController;
}

ACameraActor* APongPlayerStart::GetCamera()
{
	return OwningCamera;
}

APongGoalZone* APongPlayerStart::GetGoalZone()
{
	return GoalZone;
}
