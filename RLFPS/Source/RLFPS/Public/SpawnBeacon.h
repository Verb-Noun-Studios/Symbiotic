// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeaconActor.h"
#include "GruntCharacter.h"
#include "SpawnBeacon.generated.h"


USTRUCT()
struct FSpawnBeaconTrail {
	GENERATED_BODY()

public:
	FSpawnBeaconTrail() {};
	
	FVector end;

	float t;
	float delay;
	float speed;

	AActor* trail;
};
/**
 * 
 */
UCLASS()
class RLFPS_API ASpawnBeacon : public ABeaconActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 EnemySpawnCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float SpawnRadius;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AGruntCharacter> EnemiesToSpawn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AActor> Trail;

	virtual void Tick(float dt);

	void OnBeaconActivate_Implementation() override;

private:

	TArray<FSpawnBeaconTrail> SpawnTrails;

	TArray<TWeakObjectPtr<AGruntCharacter>> EnemiesToKill;


	bool AreAllEnemiesDead();
};
