// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	enemiesSpawned = 0;
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	elapsedTime += DeltaTime;

	if (activated)
	{
		if (elapsedTime >= 60.0 / SpawnRate)
		{
			bool spawned = false;

			while (!spawned)
			{
				SpawnEnemy(spawned);
			}


			enemiesSpawned++;
			UE_LOG(LogTemp, Warning, TEXT("Enemy Spawned: %d"), enemiesSpawned);
			elapsedTime = 0;

		}
	}

	

}

