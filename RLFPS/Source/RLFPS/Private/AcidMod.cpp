// Fill out your copyright notice in the Description page of Project Settings.


#include "AcidMod.h"
#include "Acid.h"
#include "Gun.h"

UAcidMod::UAcidMod()
{

	
}


UAcidMod::~UAcidMod()
{

}

void UAcidMod::OnHit_Implementation(AActor* hitActor, UWorld* world)
{
	UWorld* World = world;
	FActorSpawnParameters* SpawnParams = new FActorSpawnParameters;
	SpawnParams->Owner = hitActor;
	SpawnParams->Instigator = hitActor->GetInstigator();
	SpawnParams->SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	float tempChance = FMath::RandRange(0.0f, 1.0f);

	if (tempChance < chance + additionalchancePerStack * stacks)
	{
		AActor* acidActor = World->SpawnActor<AActor>(acidActorClass, hitActor->GetActorLocation(), hitActor->GetActorRotation(), *SpawnParams);

		AAcid* acid = Cast<AAcid>(acidActor);

		acid->damage = damage;
		acid->duration = duration;
		acid->interval = interval;

		//UE_LOG(LogTemp, Warning, TEXT("Spawning Acid"));

	}


	
}