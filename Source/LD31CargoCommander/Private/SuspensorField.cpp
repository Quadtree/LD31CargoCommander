// Fill out your copyright notice in the Description page of Project Settings.

#include "LD31CargoCommander.h"
#include "SuspensorField.h"
#include "EngineUtils.h"
#include "Crate.h"
#include "Components/DestructibleComponent.h"
#include "PhysXIncludes.h"
#include "LD31CargoCommanderGameMode.h"

void ASuspensorField::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ALD31CargoCommanderGameMode* gm = Cast<ALD31CargoCommanderGameMode>(GetWorld()->GetAuthGameMode());

	if (!gm || !gm->GameRunning)
	{
		IsOn = false;
		return;
	}

	FVector delta = Destination - GetActorLocation();
	float moveAmt = MoveSpeed * DeltaSeconds;

	FVector movement(0, 0, 0);

	//movement = delta;
	//movement.Normalize();
	//movement *= MoveSpeed / 4;
	
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

	if (IsOn)
	{
		for (auto i = TActorIterator<ACrate>(GetWorld()); i; ++i)
		{
			UDestructibleComponent* Destructible = i->FindComponentByClass<UDestructibleComponent>();
			TArray<FName> bones;

			Destructible->GetBoneNames(bones);

			for (auto i = bones.CreateIterator(); i; ++i)
			{
				FVector pos = Destructible->GetBoneLocation(*i);

				FVector delta = pos - GetActorLocation();

				if (delta.Size2D() < 900)
				{
					int32 chunkIdx = Destructible->BoneIdxToChunkIdx(Destructible->GetBoneIndex(*i));
					if (Destructible->ChunkInfos.Num() > chunkIdx && Destructible->ChunkInfos[chunkIdx].Actor)
					{

						/*if (Destructible->ChunkInfos[chunkIdx].Actor->getLinearVelocity().magnitude() < 0.001f)
						{
							UE_LOG(LLog, Display, TEXT("AWAKEN!!"));
							Destructible->ChunkInfos[chunkIdx].Actor->setLinearVelocity(PxVec3(0, 0, 100.f));
						}*/

						//float upMove = 0;

						//if (pos.Z < 800) upMove = 500;

						FVector target = GetActorLocation();
						target.Z = 800;

						movement = target - pos;
						movement.Normalize();
						movement *= 500;

						Destructible->ChunkInfos[chunkIdx].Actor->setLinearVelocity(PxVec3(movement.X, movement.Y, movement.Z));

					}
				}
			}
		}
	}
}

void ASuspensorField::SetIsOn(bool isOnTheParameter)
{
	this->IsOn = isOnTheParameter;
}