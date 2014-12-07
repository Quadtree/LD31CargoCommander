// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "SuspensorField.generated.h"

/**
 * 
 */
UCLASS()
class LD31CARGOCOMMANDER_API ASuspensorField : public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = Status)
	bool IsOn;
	
	UPROPERTY(BlueprintReadOnly, Category = Status)
	FVector Destination;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed)
	float MoveSpeed;

	UFUNCTION(BlueprintCallable, Category = Status)
	void SetIsOn(bool isOnTheParameter);
	
	virtual void Tick(float DeltaSeconds) override;
};
