// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawningActor.generated.h"

UCLASS()
class RLFPS_API ASpawningActor : public AActor
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float elapsedTime = 0;
	bool activated = true;
	AActor* player;
	float distanceToPlayer;
	FVector location;
	

public:	
	// Sets default values for this actor's properties
	ASpawningActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> playerClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> classToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EPM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float spawnRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxEnemies;
	int enemiesSpawned = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float distanceToPlayerThreshold = 4000;

	FActorSpawnParameters* spawnParams;


	float beaconTime = 0;
	float beaconMultiplier = 0;

	void SpawnEnemie();
	UFUNCTION(BlueprintCallable)
	void Activate() { activated = true; };
	UFUNCTION(BlueprintCallable)
	void Deactivate() { activated = false; };

	void ActivateWithBeacon(float BeaconTime, float BeaconMultiplier);

};
