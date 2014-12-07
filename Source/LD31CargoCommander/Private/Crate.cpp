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

	for (auto i = bones.CreateIterator(); i; ++i)
	{
		FVector pos = Destructible->GetBoneLocation(*i);

		int32 chunkIdx = Destructible->BoneIdxToChunkIdx(Destructible->GetBoneIndex(*i));
		if (Destructible->ChunkInfos.Num() > chunkIdx && Destructible->ChunkInfos[chunkIdx].Actor)
		{
			physx::PxVec3 force(0,0,0);

			if (pos.Y > -4700)
			{
				force.z = -980.f * DeltaSeconds;
			}

			for (auto j = TActorIterator< ACrateMover >(GetWorld()); j; ++j)
			{
				force += physx::PxVec3(j->Movement.X * DeltaSeconds, j->Movement.Y * DeltaSeconds, j->Movement.Z * DeltaSeconds);
			}

			UE_LOG(LLog, Display, TEXT("FORCE %s %s %s"), *FString::SanitizeFloat(force.x), *FString::SanitizeFloat(force.y), *FString::SanitizeFloat(force.z));

			Destructible->ChunkInfos[chunkIdx].Actor->setLinearVelocity(Destructible->ChunkInfos[chunkIdx].Actor->getLinearVelocity() + force);

			if (pos.Y < -10000)
			{
				Destroy();
				return;
			}
		}
	}
}

int32 ACrate::GetValue()
{
	int32 pieces = 0;

	TArray<FName> bones;

	Destructible->GetBoneNames(bones);

	for (auto i = bones.CreateIterator(); i; ++i)
	{
		int32 chunkIdx = Destructible->BoneIdxToChunkIdx(Destructible->GetBoneIndex(*i));
		if (Destructible->ChunkInfos.Num() > chunkIdx && Destructible->ChunkInfos[chunkIdx].Actor)
		{
			pieces++;
		}
	}

	//UE_LOG(LLog, Display, TEXT("N %s"), *FString::FromInt(pieces));

	return pieces == 2 ? CrateValue : 0;
}