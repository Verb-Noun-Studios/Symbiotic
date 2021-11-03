// Fill out your copyright notice in the Description page of Project Settings.


#include "ModBase.h"
#include "Bullet.h"


UModBase::UModBase()
{
}

UModBase::~UModBase()
{
}


void UModBase::OnApply_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Base Mod On Apply"));
}

void UModBase::OnSpawn_Implementation(ABullet* bullet)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Base Mod On Spawn"));
}

void UModBase::OnFire_Implementation(AGun* gun)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Base Mod On Fire"));
}

void UModBase::OnHit_Implementation(AActor* hitActor, UWorld* world)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Test On Hit"));
}

void UModBase::OnReload_Implementation(AActor* player)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Test On Reload"));
}


AActor* UModBase::GetActorOfClass_Internal(TSubclassOf<AActor> actorClass)
{
	UWorld* world = GetWorld();

	return UGameplayStatics::GetActorOfClass(world, actorClass);
	
}