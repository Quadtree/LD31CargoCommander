// Fill out your copyright notice in the Description page of Project Settings.

#include "LD31CargoCommander.h"
#include "LD31PlayerController.h"
#include "SuspensorField.h"

ALD31PlayerController::ALD31PlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALD31PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FHitResult res;

	GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, true, res);

	ASuspensorField* sf = Cast<ASuspensorField>(GetPawn());

	if (sf && res.bBlockingHit)
	{
		FVector dest = res.Location;
		
		dest.X = FMath::Clamp(dest.X, -2660.f, 4180.f);
		dest.Y = FMath::Clamp(dest.Y, -4270.f, 4050.f);
		dest.Z = 350;

		sf->Destination = dest;

		//UE_LOG(LLog, Display, TEXT("Dest %s"), *dest.ToCompactString());
	}

	
}