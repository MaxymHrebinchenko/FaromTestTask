// Fill out your copyright notice in the Description page of Project Settings.
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, text)

#include "PongPlatform.h"
#include "EnhancedInputSubsystems.h"
#include <EnhancedInputComponent.h>
#include "PongMappingContext.h"

// Sets default values
APongPlatform::APongPlatform()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	if (RootComponent)
		RootComponent->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void APongPlatform::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APongPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}