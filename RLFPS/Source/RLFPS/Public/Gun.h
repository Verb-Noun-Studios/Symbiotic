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
	/*
	* Adds a mod to the list. If the mod is already in the list it adds to its stacks
	*/
	UFUNCTION(BlueprintCallable)
	void AddMod(UModBase* mod);
	
	/*
	* Gets the state of the keys
	*/
	bool GetFireKey();
	bool GetReloadKey();
	bool GetOptionOneKey();
	bool GetOptionTwoKey();

	/*
	* Blueprint callable function to call Onhit effects for mods
	*/
	UFUNCTION(BlueprintCallable)
	void OnHitCallback(AActor* actor);
	
	UFUNCTION(BlueprintCallable)
	void OnHitCallbackWithSkip(AActor* actor, FName name);

	/*
	* Spawns a bullet If enough time has passed to amch the RPM. Calls mods OnFire functions.
	*/
	void Fire(float deltaTime);
	
	/*
	* This calls reload effects on mods and will also be used to potentially play animations or sounds
	*/
	void Reload();

	/*
	* These are used to spawn rounds. 
	* Both call OnSpawn effects but the seccond one is used to modify the direction of the bullet and the location it is spawned.
	*/
	void SpawnRound(FActorSpawnParameters spawnParams);
	void SpawnRound(FActorSpawnParameters spawnParams, FVector offset, FVector dir);

	/*
	* This is a Blueprint callable function that adds exp to the gun. Preps gun to level up when necessary.
	*/
	UFUNCTION(BlueprintCallable)
	void GainEXP(int exp);
	
	/*
	* This is a Blueprint callable function to get level progress.
	*/
	UFUNCTION(BlueprintCallable)
	float GetLevelPercentage();
	
	/*
	* Gets a new set of two random mods. Sets ModOptions.
	*/
	TArray<UModBase*> GetNewModOptions();

	/*
	* Returns the current Mod Options. Blueprint callable.
	*/
	UFUNCTION(BlueprintCallable)
	TArray<UModBase*> GetModOptions();
	
	/*
	* Levels up the Gun and adds mod based on parameter.
	*/
	void LevelUp(UModBase* newModType);

	/*
	* Updates RPM, reload time, and ammo count based on mods.
	*/
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
	FActorSpawnParameters* spawnParams;

	
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
