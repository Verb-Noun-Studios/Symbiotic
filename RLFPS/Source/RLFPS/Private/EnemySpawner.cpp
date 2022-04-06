// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "Kismet/KismetMathLibrary.h"
//#include "NavigationSystem.h"

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
	//SpawnInitialEnemies();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	elapsedTime += DeltaTime;

	if (activated)
	{

		if (boostTime > 0)
		{
			boostTime -= DeltaTime;

			if (elapsedTime >= 60.0 / (SpawnRate * boostMultiplier))
			{
				bool spawned = false;
				int attempts = 0;
				while (!spawned && attempts < 10)
				{
					attempts++;
					SpawnEnemy(spawned);
				}
				

				enemiesSpawned++;
				elapsedTime = 0;
				UE_LOG(LogTemp, Warning, TEXT("SpawningActor: %d"), enemiesSpawned);
			}
		}
		else
		{
			if (elapsedTime >= 60.0 / SpawnRate)
			{
				bool spawned = false;

				int attempts = 0;
				while (!spawned && attempts < 10)
				{
					attempts++;
					SpawnEnemy(spawned);
				}


				enemiesSpawned++;
				elapsedTime = 0;
				UE_LOG(LogTemp, Warning, TEXT("SpawningActor: %d"), enemiesSpawned);
			}	
		}
	}

	

}

void AEnemySpawner::Boost(float BeaconTime, float BeaconMultiplier)
{
	boostTime = BeaconTime;
	boostMultiplier = BeaconMultiplier;
}

void AEnemySpawner::SpawnInitialEnemies()
{
	
	for (int i = 0; i < InitialEnemies; i++)
	{
		
		bool spawned = false;
		int attempts = 0;
 		while (!spawned && attempts < 10)
		{
			attempts++;
			SpawnEnemy(spawned);
		}
		
	}
}


bool AEnemySpawner::GetRandomNavPoint(FVector& out_point) {
	if (PolyCache.Num() == 0) {
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
		ARecastNavMesh* NavData = (ARecastNavMesh*)NavSys->GetDefaultNavDataInstance();

		FVector pos = GetActorLocation();
		FBox box(pos, pos);
		box = box.ExpandBy(3000);
		NavData->GetPolysInBox(box, PolyCache);
	}

	// TODO: (thornton) this might cause alot of lag if there is no mesh yet
	if (PolyCache.Num() == 0) return false;

	const int32 RandomIndex = FMath::RandHelper(PolyCache.Num());
	const FNavPoly& Poly = PolyCache[RandomIndex];

	//return FNavLocation(Poly.Center, Poly.Ref);
	out_point = Poly.Center;
	return true;
}