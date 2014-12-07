// Fill out your copyright notice in the Description page of Project Settings.

#include "LD31CargoCommander.h"
#include "LD31HUD.h"
#include "EngineUtils.h"
#include "Crate.h"
#include "LD31CargoCommanderGameMode.h"

int32 ALD31HUD::GetRemainingCrateValue()
{
	int32 totalValue = 0;

	for (auto i = TActorIterator<ACrate>(GetWorld()); i; ++i)
	{
		totalValue += i->GetValue();
	}

	return totalValue;
}

float ALD31HUD::GetTimeLeft()
{
	ALD31CargoCommanderGameMode* gm = Cast<ALD31CargoCommanderGameMode>(GetWorld()->GetAuthGameMode());

	if (gm)
	{
		return gm->TimeLeft;
	}

	return -1;
}