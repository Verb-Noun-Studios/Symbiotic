// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaconActor.h"
#include "SpawningActor.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

// Sets default values
ABeaconActor::ABeaconActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABeaconActor::BeginPlay()
{
	Super::BeginPlay();
	GetSpawnPoints();
	timeRemaining = time;
}

// Called every frame
void ABeaconActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (activated)
	{
		timeRemaining -= DeltaTime;
		
		if (timeRemaining < 0)
		{
			eventComplete = true;
		}
	}
	
	
	
}

void ABeaconActor::GetSpawnPoints()
{

	for (TActorIterator<ASpawningActor> it(GetWorld()); it; ++it)
	{

		FVector dir = it->GetActorLocation() - GetActorLocation();
		if (dir.SizeSquared() < radius * radius)
		{
			spawnPoints.Add(*it);
		}
	}
}

void ABeaconActor::Activate()
{
	

	UE_LOG(LogTemp, Warning, TEXT("Activating"));
	if (activated && !eventComplete)
	{
		for (ASpawningActor* spawnPoint : spawnPoints)
		{
			spawnPoint->ActivateWithBeacon(time, multiplier);
		}
	}
	
}

void ABeaconActor::RecieveOnActivate_Implementation()
{

}


void ABeaconActor::Use()
{
	UE_LOG(LogTemp, Warning, TEXT("Using"));
	activated = true;
	Activate();
	RecieveOnActivate();
}

