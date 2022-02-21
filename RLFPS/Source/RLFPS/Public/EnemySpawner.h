// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class RLFPS_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	float roomHalflength = 300;

	bool roomCleared = false;
	bool activated = false;
	int emnemiesKilled = 0;
	int enemiesSpawned = 0;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRate = 10;
	float elapsedTime = 0;



	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnEnemy(bool& spawned);

};
