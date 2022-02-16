// Fill out your copyright notice in the Description page of Project Settings.


#include "SymbioticGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SpawningActor.h"
#include "Engine.h"

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
	//int rNum = FMath::RandRange(minRoomstoSpawn, maxRoomstoSpawn);
	//ULevelStreaming* instance;
	//for (int i = 0; i < 5; i++)
	//{
	//	int tNum = 0;
	//	FLatentActionInfo info;
	//	FName temp = LevelsToLoadTier1[tNum];
	//	UGameplayStatics::LoadStreamLevel(GetWorld(), temp, false, false, info);
	//	ULevelStreaming* Level = UGameplayStatics::GetStreamingLevel(GetWorld(), temp);

	//	instance = Level->CreateInstance(FString::FString(temp.ToString() + "%i", i));
	//	instance->SetShouldBeLoaded(true);
	//	MapTransform.SetLocation(FVector(MapTransform.GetLocation().X * i, 0.0, 0.0));
	//	instance->LevelTransform = MapTransform;
	//	instance->SetShouldBeVisible(true);
	//}

}