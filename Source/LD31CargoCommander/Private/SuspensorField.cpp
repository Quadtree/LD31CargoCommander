// Fill out your copyright notice in the Description page of Project Settings.

#include "LD31CargoCommander.h"
#include "SuspensorField.h"

void ASuspensorField::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector delta = Destination - GetActorLocation();
	float moveAmt = MoveSpeed * DeltaSeconds;
	
	if (delta.Size() > moveAmt)
	{
		delta.Normalize();
		delta *= moveAmt;

		RootComponent->MoveComponent(delta, FRotator::ZeroRotator, false);
	}
	else
	{
		RootComponent->SetWorldLocation(Destination);
	}
}

void ASuspensorField::SetIsOn(bool isOnTheParameter)
{
	this->IsOn = isOnTheParameter;
}