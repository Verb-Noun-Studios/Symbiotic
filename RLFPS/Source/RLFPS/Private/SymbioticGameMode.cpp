// Fill out your copyright notice in the Description page of Project Settings.


#include "SymbioticGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SpawningActor.h"

void ASymbioticGameMode::StartPlay()
{
	Super::StartPlay();
	enemiesLeftToSpawn = maxEnemies;
	SpawnLevel();
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

void ASymbioticGameMode::SpawnLevel() 
{
	FLatentActionInfo LatentInfo;
	FName temp = "Blockout1";
	UGameplayStatics::LoadStreamLevel(this, temp, true, true, LatentInfo);
	ULevelStreaming* Level = UGameplayStatics::GetStreamingLevel(GetWorld(), temp);
	

}