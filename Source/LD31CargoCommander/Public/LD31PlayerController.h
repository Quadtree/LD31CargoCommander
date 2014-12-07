// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "LD31PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LD31CARGOCOMMANDER_API ALD31PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ALD31PlayerController(const FObjectInitializer& ObjectInitializer);
	
	virtual void Tick(float DeltaSeconds) override;
	
	
};
