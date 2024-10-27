// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "IA_Move.h"

#include "PongMappingContext.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API UPongMappingContext : public UInputMappingContext
{
	GENERATED_BODY()
protected:
	UIA_Move* Move;
	UInputModifierNegate* Negate;
	UInputModifierScalar* Scalar;

	FEnhancedActionKeyMapping Right;
	FEnhancedActionKeyMapping Left;
public:
	UPongMappingContext();
	FEnhancedActionKeyMapping GetMoveMapping();
	void SetSpeed(float Speed);
};
