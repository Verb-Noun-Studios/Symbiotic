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


void UModBase::OnApply_Implementation(AFragPlayer* player)
{
}

void UModBase::OnSpawn_Implementation(ABullet* bullet)
{
}

void UModBase::OnFire_Implementation(AGun* gun)
{
}

void UModBase::OnHit_Implementation(AActor* hitActor, UWorld* world)
{
}

void UModBase::OnReload_Implementation(AActor* player)
{
}

void UModBase::OnUpdateBulletVFX_Implementation(ABullet* bullet)
{
}

void UModBase::OnLowHealth_Implementation(float deltaTime)
{
}




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

AActor* UModBase::SpawnActorOfClass_Internal(AActor* owner, TSubclassOf<AActor> actorClass, FVector const& loc, FRotator const& rot)
{

	UWorld* World = GetWorld();
	FActorSpawnParameters* SpawnParams = new FActorSpawnParameters;
	SpawnParams->Owner = owner;
	SpawnParams->SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* actor = World->SpawnActor<AActor>(actorClass, loc, rot, *SpawnParams);

	return actor;
}