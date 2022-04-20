// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavMesh/RecastNavMesh.h"
#include "NavigationSystem.h"
#include "EnemySpawner.generated.h"

USTRUCT(BlueprintType)
struct FEnemySpawnChoice {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float chance;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> type;
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int emnemiesKilled = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int enemiesSpawned = 0;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRate = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InitialEnemies = 10;
	float elapsedTime = 0;
	
	// List of the types we can spawn along with the chance to spawn
	// will default to the last item in the array
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEnemySpawnChoice> SpawnChoices;

	float boostTime = 0;
	float boostMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool activated = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool roomCleared = false;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnEnemy(bool& spawned);
	UFUNCTION(BlueprintCallable)
	void SetActivated(bool newStatus) { activated = newStatus; };
	UFUNCTION(BlueprintCallable)
	bool GetActivated() { return activated; };
	UFUNCTION(BlueprintCallable)
	void Boost(float Time, float Multiplier);
	UFUNCTION(BlueprintCallable)
	void SpawnInitialEnemies();

	bool SpawnEnemy();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSpawnEnemy(AActor* actor);

	bool TrySpawn();
	bool TrySpawnMultiple(int count);

	UFUNCTION(BlueprintCallable)
	TSubclassOf<AActor> GetRandomType();

private:
	TArray<FNavPoly> PolyCache;

	class AFragPlayer* Player;



public:

	UFUNCTION(BlueprintCallable)
	bool GetRandomNavPoint(FVector& out_point);
};
