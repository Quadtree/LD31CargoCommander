// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "LD31CargoCommander.h"
#include "LD31CargoCommanderGameMode.h"
#include "LD31CargoCommanderPawn.h"
#include "CrateMover.h"

ALD31CargoCommanderGameMode::ALD31CargoCommanderGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// set default pawn class to our character class
	DefaultPawnClass = ALD31CargoCommanderPawn::StaticClass();

	TimeLeft = 240;
	TimeToNextHazard = 1;
	HasDoneAcceleration = false;
	AvgTimeBetweenHazards = 15;
	HazardSpinPower = 0.001f;
	HazardPushPower = 700;
	AvgHazardDuration = 7;
	GameRunning = false;
}

void ALD31CargoCommanderGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!GameRunning) return;

	if (TimeLeft <= 0.0001f)
	{
		TimeLeft = 0;
		OnRunEnded();
		GameRunning = false;
	}
	else
	{
		TimeLeft -= DeltaSeconds;

		TimeToNextHazard -= DeltaSeconds;

		if (TimeToNextHazard <= 0)
		{
			if (!HasDoneAcceleration)
			{
				ACrateMover* cm = GetWorld()->SpawnActor<ACrateMover>();
				cm->Movement.X = HazardPushPower * -0.15f;
				cm->LifeSpan = 25;
				HasDoneAcceleration = true;
			}
			else
			{
				ACrateMover* cm = GetWorld()->SpawnActor<ACrateMover>();

				//if (FMath::Rand() % 2 == 0)
				//{
				//	cm->Spin = FMath::FRandRange(-HazardSpinPower, HazardSpinPower);
				//	Messages.Add(TEXT("Pilot: Whoa! An asteroid!"));
				//}
				//else
				{
					cm->Movement.X = FMath::FRandRange(-HazardPushPower, HazardPushPower);
					cm->Movement.Y = FMath::FRandRange(-HazardPushPower, HazardPushPower);
					cm->Movement.Normalize();
					cm->Movement *= HazardPushPower;
					Messages.Add(TEXT("Pilot: Whoops, wrong button!"));
				}

				cm->LifeSpan = AvgHazardDuration * FMath::RandRange(0.5f, 1.5f);

				UE_LOG(LLog, Display, TEXT("SPIN %s MOVE %s"), *FString::SanitizeFloat(cm->Spin), *cm->Movement.ToCompactString())
			}

			TimeToNextHazard = FMath::FRandRange(0.75f, 1.25f) * AvgTimeBetweenHazards;
		}
	}

	

	
}