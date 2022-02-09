// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SymbioticGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RLFPS_API ASymbioticGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
		void StartPlay();


		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxEnemies = 50;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int enemiesLeftToSpawn;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int EXPRequiredForBoss = 300;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool firstBeaconFound = false;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool firstBeaconActivated = false;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Sequence")
		bool bossSequenceStarted = false;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss  Sequence")
		float increasedSpawnRate = 4.0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss  Sequence")
		float sequenceTime = 60.0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss  Sequence")
		TSubclassOf<AActor> SpawnerClass;
		UFUNCTION(BlueprintCallable)
		void StartBossSequence();
		UFUNCTION(BlueprintCallable)
		void StartIncreasedSpawnRate();
		UFUNCTION(BlueprintImplementableEvent)
		void StartTimer();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Generation")
		int maxRoomstoSpawn = 8;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Generation")
		int minRoomstoSpawn = 6;


	UPROPERTY(EditAnywhere, Category = "Level Generation")
		FName SpawnRoom;
	

	//Note: These need to be added to the level window in order to load
	//UPROPERTY(EditAnywhere, Category = "Level Generation")
		//FName LevelsToLoad[8];

private:

	void SpawnLevel();

};
