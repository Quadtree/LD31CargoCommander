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
	RootComponent = ShipMeshComponent;

	PrimaryActorTick.bCanEverTick = true;

	// Movement
	MoveSpeed = 1000.0f;

	/*// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;*/

	IsGrabbing = false;
	GrabPower = 10;
}

void ALD31CargoCommanderPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	// set up gameplay key bindings
	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(MoveRightBinding);

	InputComponent->BindAction(TEXT("Grab"), EInputEvent::IE_Pressed, this, &ALD31CargoCommanderPawn::StartGrabbing);
	InputComponent->BindAction(TEXT("Grab"), EInputEvent::IE_Released, this, &ALD31CargoCommanderPawn::StopGrabbing);
}

void ALD31CargoCommanderPawn::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).ClampMaxSize(1.0f);

	// Calculate  movement
	//const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	//UE_LOG(LLog, Display, TEXT("%s"), *GetActorLocation().ToString());

	// If non-zero size, move this actor
	if (MoveDirection.SizeSquared() > 0.0f)
	{
		//AddMovementInput(MoveDirection);
		ShipMeshComponent->AddForce(MoveDirection * MoveSpeed);

		
		

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

	FRotator rot = RootComponent->GetRelativeTransform().Rotator();
	rot.Pitch = 0;
	rot.Roll = 0;
	
	ShipMeshComponent->SetPhysicsLinearVelocity(ShipMeshComponent->GetPhysicsLinearVelocity() * FVector(0.97f, 0.97f, 1.f));
	ShipMeshComponent->SetPhysicsAngularVelocity(FVector::ZeroVector);

	if (!IsGrabbing && MoveDirection.SizeSquared() > 0.2f)
	{
		FVector curVector = GetActorForwardVector();

		FRotator angular = FRotator(0, -90, 0);

		float dp = FVector::DotProduct(angular.RotateVector(MoveDirection), curVector);

		//UE_LOG(LLog, Display, TEXT("DP %s"), *FString::SanitizeFloat(FVector::DotProduct(MoveDirection, curVector)));

		if (FVector::DotProduct(MoveDirection, curVector) < 0.9f){
			if (dp > 0)
				rot.Yaw += DeltaSeconds * 500;
			else
				rot.Yaw -= DeltaSeconds * 500;
		}
		else
		{
			rot.Yaw = MoveDirection.Rotation().Yaw;
		}
	}

	RootComponent->SetRelativeRotation(rot);

	if (IsGrabbing)
	{
		TArray<FHitResult> res;
		FCollisionQueryParams params;
		FCollisionObjectQueryParams oParams;
		params.AddIgnoredActor(this);

		//UE_LOG(LLog, Display, TEXT("SCAN!!"));

		if (GetWorld()->LineTraceMulti(res, GetActorLocation() + FVector(0, 0, 100), GetActorLocation() + FVector(0, 0, 100) + (GetActorForwardVector() * 800), params, oParams))
		{
			for (auto i = res.CreateIterator(); i; ++i)
			{
				//UE_LOG(LLog, Display, TEXT("HIT!!"));

				if (i->Actor.IsValid() && Cast<UPrimitiveComponent>(i->Actor->GetRootComponent()))
				{
					//UE_LOG(LLog, Display, TEXT("DRAG!!"));
					Cast<UPrimitiveComponent>(i->Actor->GetRootComponent())->AddForceAtLocation(GetActorForwardVector() * -GrabPower, i->ImpactPoint);
				}
			}
		}
	}
}

void ALD31CargoCommanderPawn::StartGrabbing()
{
	IsGrabbing = true;
}

void ALD31CargoCommanderPawn::StopGrabbing()
{
	IsGrabbing = false;
}