// Fill out your copyright notice in the Description page of Project Settings.


#include "AcidMod.h"

UAcidMod::UAcidMod()
{

	
}


UAcidMod::~UAcidMod()
{

}

void UAcidMod::OnHit(AActor* actor)
{
	UWorld* World = GetWorld();
	FActorSpawnParameters* SpawnParams = new FActorSpawnParameters;
	SpawnParams->Owner = actor;
	SpawnParams->Instigator = actor->GetInstigator();
	SpawnParams->SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	float tempChance = FMath::RandRange(0.0f, 1.0f);

	if (tempChance < chance + additionalchancePerStack * stacks)
	{
		AActor* acid = World->SpawnActor<AActor>(acidActorClass, actor->GetActorLocation(), actor->GetActorRotation(), *SpawnParams);
	}
	
}