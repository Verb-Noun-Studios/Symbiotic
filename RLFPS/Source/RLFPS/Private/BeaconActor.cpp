// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaconActor.h"

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
	TArray<AActor*> spawnActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), spawnerClass, spawnActors);
	for (AActor* actor : spawnActors)
	{
		//

		FVector dir = GetActorLocation() - actor->GetActorLocation();



		
		if (dir.SizeSquared() < radius * radius)
		{
			AEnemySpawner* spawner = Cast<AEnemySpawner>(actor);
			spawnPoint = spawner;
		}
	}
}

void ABeaconActor::Activate()
{
	

	UE_LOG(LogTemp, Warning, TEXT("Activating"));
	
	spawnPoint->Boost(time, multiplier);

	PlayActivationSound();
	
	
}

void ABeaconActor::RecieveOnUse_Implementation()
{

}


void ABeaconActor::Use()
{
	UE_LOG(LogTemp, Warning, TEXT("Using"));

	if (!activated) 
	{
		GetSpawnPoints();
		activated = true;
		Activate();
	}
	
	RecieveOnUse();
}

