// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModBase.h"
#include <vector>
#include "NiagaraSystem.h"
#include "Gun.generated.h"



class UCameraComponent; 

UCLASS()
class RLFPS_API AGun : public AActor
{
	GENERATED_BODY()



	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;
	
	

public:	
	// Sets default values for this actor's properties
	AGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddMod(UModBase* mod);
	

	bool GetFireKey();
	bool GetReloadKey();
	bool GetOptionOneKey();
	bool GetOptionTwoKey();

	UFUNCTION(BlueprintCallable)
	void OnHitCallback(AActor* actor);

	void Fire(float deltaTime);
	void Reload();
	void SpawnRound(FActorSpawnParameters spawnParams);
	void SpawnRound(FActorSpawnParameters spawnParams, FVector offset, FVector dir);

	FActorSpawnParameters* spawnParams;


	UFUNCTION(BlueprintCallable)
	void GainEXP(int exp);
	UFUNCTION(BlueprintCallable)
	float GetLevelPercentage();
	TArray<UModBase*> GetNewModOptions();
	UFUNCTION(BlueprintCallable)
	TArray<UModBase*> GetModOptions();
	void LevelUp(UModBase* newModType);
	void UpdateCoreStats();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UModBase*> mods;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UModBase>> allMods;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* muzzleFlash;

	/*************FUNCTIONAL VARIABLES************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget = true))
	float MuzzleLocation;
	UPROPERTY(BlueprintReadWrite)
	bool firing = false;
	UPROPERTY(BlueprintReadWrite)
	int ammoRemaining;
	UPROPERTY(BlueprintReadWrite)
	bool reloading = false;
	float elapsedTime = 0;

	
	/*************DEFAULT VALUES*************/
	UPROPERTY(EditAnywhere, Category = "Game Stats")
	float defaultReloadTime = 5;
	UPROPERTY(EditAnywhere, Category = "Game Stats")
	int defaultAmmoCount = 10;
	UPROPERTY(EditAnywhere, Category = "Game Stats")
	int defaultRPM = 120;
	UPROPERTY(EditAnywhere, Category = "Game Stats")
	int defaultBulletSpeed = 120;
	UPROPERTY(EditAnywhere, Category = "Game Stats")
	float defaultDamage = 25;
	UPROPERTY(EditAnywhere, Category = "Game Stats")
	float reloadTimeModifierRate = 0.8;
	UPROPERTY(EditAnywhere, Category = "Game Stats")
	float rpmModifierRate = 1.5;
	UPROPERTY(EditAnywhere, Category = "Game Stats")
	float ammoModifierRate = 0.8;

	/****************RUNTIME GUN STATS***************/
	UPROPERTY(EditAnywhere, Category = "Gun Stats")
	float reloadTime;
	UPROPERTY(EditAnywhere, Category = "Gun Stats", BlueprintReadWrite)
	int ammoCount;
	UPROPERTY(EditAnywhere, Category = "Gun Stats")
	float bulletSpeed;
	UPROPERTY(EditAnywhere, Category = "Gun stats")
	int rpm;
	UPROPERTY(BlueprintReadWrite, Category = "Game Stats")
	float Damage = 25;
	//int shotsPerRound = 1;




	UPROPERTY(EditAnywhere, Category = "Controls")
	FKey FireKey;
	UPROPERTY(EditAnywhere, Category = "Controls")
	FKey ReloadKey;
	UPROPERTY(EditAnywhere, Category = "Controls")
	FKey OptionOneKey;
	UPROPERTY(EditAnywhere, Category = "Controls")
	FKey OptionTwoKey;

	UPROPERTY(BlueprintReadWrite)
	int totalEXP;
	UPROPERTY(BlueprintReadWrite)
	int expToNextLevel = 5;
	UPROPERTY(BlueprintReadWrite)
	int currentEXP;
	UPROPERTY(BlueprintReadWrite)
	bool readyToLevelUp = false;
	UPROPERTY(BlueprintReadWrite)
	TArray<UModBase*> ModOptions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float levelingRate = 1.5;




	/*RETICLE RELATED THINGS*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxRaycastDistance = 2000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float minRaycastDistance = 300;
	UFUNCTION()
	FVector RaycastFromCamera();

	void LogFVector(FVector vector)  { UE_LOG(LogTemp, Warning, TEXT("X: %f  Y: %f  Z: %f"), vector.X, vector.Y, vector.Z); };
};
