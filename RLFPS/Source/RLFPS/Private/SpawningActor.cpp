// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningActor.h"

// Sets default values
ASpawningActor::ASpawningActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawningActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("SpawningActor!"));

	FActorSpawnParameters* SpawnParams = new FActorSpawnParameters;
	SpawnParams->Owner = this;
	SpawnParams->Instigator = GetInstigator();
	SpawnParams->SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	spawnParams = SpawnParams;
}

// Called every frame
void ASpawningActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	elapsedTime += DeltaTime;

	
	if (beaconTime > 0)
	{
		beaconTime -= DeltaTime;

		
		if (elapsedTime > (60.0/ (EPM * beaconMultiplier)) && (enemiesSpawned < maxEnemies || maxEnemies < 1))
		{
			SpawnEnemie();
			elapsedTime = 0;
		}
		
	}
	else
	{
		if (elapsedTime > (60.0/EPM) && (enemiesSpawned < maxEnemies || maxEnemies < 1))
		{
			SpawnEnemie();
			elapsedTime = 0;
		}
	}
	
	

}

void ASpawningActor::SpawnEnemie()
{

	FVector spawnOffset(FMath::RandPointInCircle(spawnRadius),0);

	UWorld* World = GetWorld();
	AActor* enemie = World->SpawnActor<AActor>(classToSpawn, GetActorLocation() + spawnOffset, GetActorRotation(), *spawnParams);

	if (!enemie)
	{
		SpawnEnemie();
	}
	else
	{
		enemiesSpawned++;
		
	}
		
	
}

void ASpawningActor::ActivateWithBeacon(float BeaconTime, float BeaconMultiplier)
{
	beaconTime = BeaconTime;
	beaconMultiplier = BeaconMultiplier;
	Activate();
}