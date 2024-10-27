// Fill out your copyright notice in the Description page of Project Settings.


#include "PongBall.h"

// Sets default values
APongBall::APongBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bReplicates = true;
	SetReplicateMovement(true);
	if (RootComponent)
	{
		RootComponent->SetIsReplicated(true);
	}
}

void APongBall::ResetBall()
{
	SetActorLocation(StartPos, false, nullptr, ETeleportType::ResetPhysics);
}

void APongBall::SetRandomAngle()
{
	if (HasAuthority())
	{
		//StartPos = GetActorLocation();
		//Random start angle
		float Direction = FMath::FRand();
		if (Direction > 0.5)
		{
			Direction = 180;
		}
		else
		{
			Direction = 0;
		}
		float Angle = FMath::RandRange(-35.f + Direction, 35.f + Direction); //Random start angle
		SetActorRotation(FRotator(0, Angle, 0));
	}
}

// Called when the game starts or when spawned
void APongBall::BeginPlay()
{
	Super::BeginPlay();
	StartPos = GetActorLocation();
}

// Called every frame
void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FHitResult HitResult;
		FVector Forward = GetActorForwardVector();
		AddActorWorldOffset(GetWorld()->DeltaTimeSeconds * Forward * Speed, true,&HitResult);
		if (HitResult.bBlockingHit)
		{
			FVector Reflected = Forward - 2 * FVector::DotProduct(Forward,HitResult.Normal) * HitResult.Normal; 

			// Convert the reflected vector to a rotation
			SetActorRotation(Reflected.Rotation());
		}
	}
}

