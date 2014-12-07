// Fill out your copyright notice in the Description page of Project Settings.

#include "LD31CargoCommander.h"
#include "Crate.h"
#include "Components/DestructibleComponent.h"
#include "PhysXIncludes.h"
#include "CrateMover.h"
#include "EngineUtils.h"

ACrate::ACrate(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Destructible = ObjectInitializer.CreateDefaultSubobject<UDestructibleComponent>(this, TEXT("Destructible"));
	RootComponent = Destructible;

	PrimaryActorTick.bCanEverTick = true;
}

void ACrate::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TArray<FName> bones;

	Destructible->GetBoneNames(bones);

	for (auto i = bones.CreateIterator(); i; ++i){
		//UE_LOG(LLog, Display, TEXT("TICK!!! %s %s"), *i->ToString(), *Destructible->GetBoneLocation(*i).ToCompactString());

		FVector pos = Destructible->GetBoneLocation(*i);

		int32 chunkIdx = Destructible->BoneIdxToChunkIdx(Destructible->GetBoneIndex(*i));
		if (Destructible->ChunkInfos.Num() > chunkIdx && Destructible->ChunkInfos[chunkIdx].Actor)
		{
			physx::PxVec3 force;

			if (pos.Y < -4700)
			{
				PxVec3 vel = Destructible->ChunkInfos[chunkIdx].Actor->getLinearVelocity();
				vel.z = 0;

				Destructible->ChunkInfos[chunkIdx].Actor->setLinearVelocity(vel);
			}

			for (auto j = TActorIterator< ACrateMover >(GetWorld()); j; ++j)
			{
				force += physx::PxVec3(j->Movement.X * DeltaSeconds, j->Movement.Y * DeltaSeconds, j->Movement.Z * DeltaSeconds);

				UE_LOG(LLog, Display, TEXT("FOOORCE! %s %s %s"), *FString::SanitizeFloat(force.x), *FString::SanitizeFloat(force.y), *FString::SanitizeFloat(force.z));

				FVector rotMove = pos;
				rotMove = FRotator(0, 90, 0).RotateVector(rotMove);

				rotMove *= j->Spin;

				force += physx::PxVec3(rotMove.X * DeltaSeconds, rotMove.Y * DeltaSeconds, rotMove.Z * DeltaSeconds);
			}

			if (force.magnitude() > 0.001f)
			{
				if (Destructible->ChunkInfos[chunkIdx].Actor->getLinearVelocity().magnitude() < 0.001f)
				{
					UE_LOG(LLog, Display, TEXT("AWAKEN!!"));
					Destructible->ChunkInfos[chunkIdx].Actor->setLinearVelocity(PxVec3(0, 0, 100.f));
				}
			}

			Destructible->ChunkInfos[chunkIdx].Actor->addForce(force, PxForceMode::eVELOCITY_CHANGE);

			
		}
	}

	Destructible->GetDestructibleMesh();

	if (GetActorLocation().Y < -4700)
	{
		Destructible->SetEnableGravity(false);
	}
	else
	{
		Destructible->SetEnableGravity(true);
	}
}