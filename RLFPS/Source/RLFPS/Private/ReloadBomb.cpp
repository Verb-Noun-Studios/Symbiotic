// Fill out your copyright notice in the Description page of Project Settings.


#include "ReloadBomb.h"
#include "GruntCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"



UReloadBombMod::UReloadBombMod()
{

}
UReloadBombMod::~UReloadBombMod()
{

}

void UReloadBombMod::OnReload_Implementation(AActor* actor)
{

	UNiagaraFunctionLibrary::SpawnSystemAtLocation( actor->GetWorld(), reloadBombEffect, actor->GetActorLocation(), actor->GetActorRotation(), FVector(particleSystemScale));
	UE_LOG(LogTemp, Warning, TEXT("Spawning System"));
	
	TArray<AActor*> enemies;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, enemies);

	for (AActor* enemy : enemies)
	{
		FVector dir = actor->GetActorLocation() - enemy->GetActorLocation();
		float distance = dir.Size();

		UE_LOG(LogTemp, Warning, TEXT("Reload Bomb: TestingDistance to Enemy, Distance: %f"), distance);

		if (distance < range + additionalRangePerStack * stacks)
		{
			UE_LOG(LogTemp, Warning, TEXT("Reload Bomb: Dealing Damage"));
			AGruntCharacter* character = Cast<AGruntCharacter>(enemy);

			FDamageEvent damageEvent;
			character->TakeDamage(damage + additionalDamagePerStack * stacks, damageEvent, UGameplayStatics::GetPlayerController(GetWorld(), 0), UGameplayStatics::GetActorOfClass(GetWorld(), playerClass));

			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particleSystem, actor->GetActorLocation(), actor->GetActorRotation(), true, EPSCPoolMethod::AutoRelease, true);
			
		}


	}

}