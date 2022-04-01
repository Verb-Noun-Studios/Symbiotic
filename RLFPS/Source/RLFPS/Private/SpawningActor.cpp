// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningActor.h"
#include "GruntCharacter.h"
#include "CustomGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "SymbioticGameMode.h"

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
	

	FActorSpawnParameters* SpawnParams = new FActorSpawnParameters;
	SpawnParams->Owner = this;
	SpawnParams->Instigator = GetInstigator();
	SpawnParams->SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	spawnParams = SpawnParams;



	player = UGameplayStatics::GetActorOfClass(GetWorld(), playerClass);
	location = GetActorLocation();

}

// Called every frame
void ASpawningActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	elapsedTime += DeltaTime;

	if (player && activated)
	{
		if (distanceToPlayer < distanceToPlayerThreshold)
		{
			if (beaconTime > 0)
			{
				beaconTime -= DeltaTime;


				if (elapsedTime > (60.0 / (EPM * beaconMultiplier)) && (enemiesSpawned < maxEnemies || maxEnemies < 1))
				{
					SpawnEnemie();
					elapsedTime = 0;
				}

			}
			else
			{
				if (elapsedTime > (60.0 / EPM) && (enemiesSpawned < maxEnemies || maxEnemies < 1))
				{
					SpawnEnemie();
					elapsedTime = 0;
				}
			}
			
		}


		distanceToPlayer = (location - player->GetActorLocation()).Size();
		
		
	}
	

}

void ASpawningActor::SpawnEnemie()
{

	AGameModeBase* gameMode = UGameplayStatics::GetGameMode(GetWorld());
	ASymbioticGameMode* customGameMode = Cast<ASymbioticGameMode>(gameMode);

	if (customGameMode->enemiesLeftToSpawn > 0) 
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
			customGameMode->enemiesLeftToSpawn--;
			UE_LOG(LogTemp, Warning, TEXT("SpawningActor!"));
		}
	}


	
		
	
}

void ASpawningActor::ActivateWithBeacon(float BeaconTime, float BeaconMultiplier)
{
	beaconTime = BeaconTime;
	beaconMultiplier = BeaconMultiplier;
	Activate();
	UE_LOG(LogTemp, Warning, TEXT("Activating with Beacon!"));
}

