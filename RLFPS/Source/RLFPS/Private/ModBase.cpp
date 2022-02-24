// Fill out your copyright notice in the Description page of Project Settings.


#include "ModBase.h"
#include "Bullet.h"
#include "NiagaraFunctionLibrary.h"


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
//
//void UModBase::OnActiveAbility_Implementation(AActor* player)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Calling Test On Active"));
//}


AActor* UModBase::GetActorOfClass_Internal(TSubclassOf<AActor> actorClass)
{
	UWorld* world = GetWorld();

	return UGameplayStatics::GetActorOfClass(world, actorClass);
	
}

TArray<AActor*> UModBase::GetActorsOfClass_Internal(TSubclassOf<AActor> actorClass)
{
	UWorld* world = GetWorld();
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(world, actorClass, OutActors);
	return OutActors;

}


UWorld* UModBase::GetWorld_Internal()
{
	return GetWorld();
}


UNiagaraComponent* UModBase::SpawnSystemAtLocation_Internal( UNiagaraSystem* system, FVector location, FRotator rotation, FVector scale)
{
	return UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), system, location, rotation, scale);
}

uint32 UModBase::GetID() {
	if (id != 0)
		id = TextKeyUtil::HashString(name.ToString());
	return id;
}