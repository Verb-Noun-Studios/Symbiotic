// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningActor.h"
#include "GruntCharacter.h"
#include "EngineUtils.h"

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
	UWorld* World = GetWorld();
	FHitResult result;
	FVector start = GetActorLocation();
	FCollisionQueryParams CollisionParameters;
	FVector end;

	for (TActorIterator<AGruntCharacter> it(GetWorld()); it; ++it)
	{
		CollisionParameters.AddIgnoredActor(*it);
		
	}

	
	do
	{

		FVector spawnOffset(FMath::RandPointInCircle(spawnRadius), 0);

		end = start + spawnOffset;
		World->LineTraceSingleByChannel(result, start, end, ECollisionChannel::ECC_Visibility);

	} while (result.Actor != nullptr);
	

	
	AActor* enemie = World->SpawnActor<AActor>(classToSpawn, end, GetActorRotation(), *spawnParams);

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