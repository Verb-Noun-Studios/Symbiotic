// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveItem.h"

UActiveItem::UActiveItem()
{

}

UActiveItem::~UActiveItem()
{

}

void UActiveItem::OnActiveAbility_Implementation(AActor* gun)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling base active item."));
}

AActor* UActiveItem::SpawnActorOfClass_Internal(AActor* owner, TSubclassOf<AActor> actorClass, FVector const& loc, FRotator const& rot)
{
	
	UWorld* World = GetWorld();
	FActorSpawnParameters* SpawnParams = new FActorSpawnParameters;
	SpawnParams->Owner = owner;
	SpawnParams->SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* actor = World->SpawnActor<AActor>(actorClass, loc, rot,  *SpawnParams);

	return actor;
}