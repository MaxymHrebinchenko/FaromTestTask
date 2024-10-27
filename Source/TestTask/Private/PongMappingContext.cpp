// Fill out your copyright notice in the Description page of Project Settings.


#include "PongMappingContext.h"

UPongMappingContext::UPongMappingContext()
{
	Move = NewObject<UIA_Move>();
	Negate = NewObject<UInputModifierNegate>();
	Scalar = NewObject<UInputModifierScalar>();
	Scalar->Scalar = FVector(800);

	Right = FEnhancedActionKeyMapping(Move, EKeys::D);
	Right.Modifiers.Add(Scalar);
	Mappings.Add(Right);
	
	Left = FEnhancedActionKeyMapping(Move, EKeys::A);
	Left.Modifiers.Add(Negate);
	Left.Modifiers.Add(Scalar);
	Mappings.Add(Left);
}

FEnhancedActionKeyMapping UPongMappingContext::GetMoveMapping()
{
	return Right;
}

void UPongMappingContext::SetSpeed(float Speed)
{
	Scalar->Scalar = FVector(Speed);
}
