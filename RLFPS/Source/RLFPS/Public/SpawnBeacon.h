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
	FSpawnBeaconTrail(FVector _start, FVector _end, TSubclassOf<AGruntCharacter> _enemyToSpawn) : start{ _start }, end{ _end }, EnemyToSpawn{ _enemyToSpawn }, t{ 0 } { speed = FVector::Dist(start, end); };
	FVector start;
	FVector end;

	TSubclassOf<AGruntCharacter> EnemyToSpawn;

	float t;
	float speed;
};
/**
 * 
 */
UCLASS()
class RLFPS_API ASpawnBeacon : public ABeaconActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnemySpawnCount;

	virtual void Use_Implementation() override;
	
	TSubclassOf<AGruntCharacter> EnemiesToSpawn;

private:

	TArray<AGruntCharacter*> EnemiesToKill;


};
