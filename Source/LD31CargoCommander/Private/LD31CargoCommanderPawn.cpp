// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "LD31CargoCommander.h"
#include "LD31CargoCommanderPawn.h"
#include "LD31CargoCommanderProjectile.h"
#include "TimerManager.h"

const FName ALD31CargoCommanderPawn::MoveForwardBinding("MoveForward");
const FName ALD31CargoCommanderPawn::MoveRightBinding("MoveRight");
const FName ALD31CargoCommanderPawn::FireForwardBinding("FireForward");
const FName ALD31CargoCommanderPawn::FireRightBinding("FireRight");

ALD31CargoCommanderPawn::ALD31CargoCommanderPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Meshes/UFO.UFO"));
	ShipMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("ShipMesh"));
	ShipMeshComponent->AttachTo(RootComponent);

	PrimaryActorTick.bCanEverTick = true;

	// Movement
	MoveSpeed = 1000.0f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

void ALD31CargoCommanderPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	// set up gameplay key bindings
	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(MoveRightBinding);
}

void ALD31CargoCommanderPawn::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).ClampMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	UE_LOG(LLog, Display, TEXT("%s"), *GetActorLocation().ToString());

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		AddMovementInput(MoveDirection);

		/*const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.SafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}*/
	}
}

