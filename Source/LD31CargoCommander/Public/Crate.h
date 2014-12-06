// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Crate.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class LD31CARGOCOMMANDER_API ACrate : public AActor
{
	GENERATED_BODY()
public:
	ACrate(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	class UDestructibleComponent* Destructible;
	
};
