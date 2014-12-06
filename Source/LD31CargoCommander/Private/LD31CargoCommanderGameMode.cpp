// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "LD31CargoCommander.h"
#include "LD31CargoCommanderGameMode.h"
#include "LD31CargoCommanderPawn.h"

ALD31CargoCommanderGameMode::ALD31CargoCommanderGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// set default pawn class to our character class
	DefaultPawnClass = ALD31CargoCommanderPawn::StaticClass();
}

