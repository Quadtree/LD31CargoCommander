// Fill out your copyright notice in the Description page of Project Settings.

#include "LD31CargoCommander.h"
#include "CrateMover.h"

void ACrateMover::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	LifeSpan -= DeltaSeconds;

	if (LifeSpan <= 0) Destroy();
}