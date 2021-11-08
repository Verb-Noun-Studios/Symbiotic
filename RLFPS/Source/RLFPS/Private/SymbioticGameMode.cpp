// Fill out your copyright notice in the Description page of Project Settings.


#include "SymbioticGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SpawningActor.h"

void ASymbioticGameMode::StartPlay()
{
	Super::StartPlay();
	enemiesLeftToSpawn = maxEnemies;
}

void ASymbioticGameMode::StartBossSequence()
{
	if (!bossSequenceStarted)
	{
		bossSequenceStarted = true;
		StartIncreasedSpawnRate();
		StartTimer();
	}
}

void ASymbioticGameMode::StartIncreasedSpawnRate()
{
	TArray<AActor*> spawnerActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpawnerClass, spawnerActors);

	UE_LOG(LogTemp, Warning, TEXT("Spawners Found: %i"), spawnerActors.Num());

	for (AActor* actor : spawnerActors)
	{
		ASpawningActor* spawner = Cast<ASpawningActor>(actor);
		spawner->ActivateWithBeacon(sequenceTime, increasedSpawnRate);
	}
	
}