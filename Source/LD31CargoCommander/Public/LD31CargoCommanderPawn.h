// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/Character.h"
#include "LD31CargoCommanderPawn.generated.h"

UCLASS(Blueprintable, Abstract)
class ALD31CargoCommanderPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

public:
	ALD31CargoCommanderPawn(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

	UPROPERTY(BlueprintReadOnly)
	bool IsGrabbing;

	UFUNCTION()
	void StartGrabbing();

	UFUNCTION()
	void StopGrabbing();
};

