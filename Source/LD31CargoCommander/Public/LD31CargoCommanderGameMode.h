// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/GameMode.h"
#include "LD31CargoCommanderGameMode.generated.h"


UCLASS(minimalapi)
class ALD31CargoCommanderGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ALD31CargoCommanderGameMode(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = Status)
	float TimeLeft;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = Hazards)
	float AvgTimeBetweenHazards;

	UPROPERTY(EditAnywhere, Category = Hazards)
	float HazardSpinPower;

	UPROPERTY(EditAnywhere, Category = Hazards)
	float HazardPushPower;

	float TimeToNextHazard;

	bool HasDoneAcceleration;

	UPROPERTY(EditAnywhere, Category = Hazards)
	float AvgHazardDuration;

	UPROPERTY(BlueprintReadWrite, Category = Game)
	bool GameRunning;

	UFUNCTION(BlueprintImplementableEvent, Category = Game)
	void OnRunEnded();

	virtual void BeginPlay() override;

	TArray<FString> Messages;
};



