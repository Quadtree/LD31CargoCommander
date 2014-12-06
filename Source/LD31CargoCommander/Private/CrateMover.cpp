// Fill out your copyright notice in the Description page of Project Settings.

#include "LD31CargoCommander.h"
#include "CrateMover.h"

ACrateMover::ACrateMover(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	LifeSpan = 10;
}

void ACrateMover::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	

	LifeSpan -= DeltaSeconds;

	if (LifeSpan <= 0){
		UE_LOG(LLog, Display, TEXT("EOL %s"), *FString::SanitizeFloat(LifeSpan));
		Destroy();
	}
}