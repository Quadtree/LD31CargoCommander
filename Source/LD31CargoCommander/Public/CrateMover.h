// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CrateMover.generated.h"

/**
 * 
 */
UCLASS()
class LD31CARGOCOMMANDER_API ACrateMover : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Move)
	FVector Movement;

	UPROPERTY(EditAnywhere, Category = Move)
	float Spin;

	UPROPERTY(EditAnywhere, Category = Life)
	float LifeSpan;
	
	virtual void Tick(float DeltaSeconds) override;
};
