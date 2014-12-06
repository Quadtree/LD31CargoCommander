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
			if (pos.Y < -4700)
			{
				//UE_LOG(LLog, Display, TEXT("FOOORCE! %s"), *FString::SanitizeFloat(980 * DeltaSeconds));
				
				Destructible->ChunkInfos[chunkIdx].Actor->addForce(physx::PxVec3(0, 0, 980 * DeltaSeconds), PxForceMode::eVELOCITY_CHANGE);
			}

			for (auto j = TActorIterator< ACrateMover >(GetWorld()); j; ++j)
			{
				Destructible->ChunkInfos[chunkIdx].Actor->addForce(physx::PxVec3(j->Movement.X * DeltaSeconds, j->Movement.Y * DeltaSeconds, j->Movement.Z * DeltaSeconds), PxForceMode::eVELOCITY_CHANGE);
			}

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