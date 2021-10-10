// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModBase.h"
#include "GunModBase.h"
#include "AmmoModBase.h"
#include "Gun.generated.h"




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

	void AddGunMod(TWeakObjectPtr<UGunModBase> mod);
	void AddAmmoMod(TWeakObjectPtr<UAmmoModBase> mod);

	bool GetFireKey();
	bool GetReloadKey();
	bool GetOptionOneKey();
	bool GetOptionTwoKey();

	void OnHitCallback(AActor* actor);

	void Fire(float deltaTime);
	void SpawnRound();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	TArray<TWeakObjectPtr<UGunModBase>> gunMods;
	TArray<TWeakObjectPtr<UAmmoModBase>> ammoMods;

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

	/****************RUNTIME GUN STATS***************/
	UPROPERTY(EditAnywhere, Category = "Gun Stats")
		float reloadTime;
	UPROPERTY(EditAnywhere, Category = "Gun Stats", BlueprintReadWrite)
		int ammoCount;
	UPROPERTY(EditAnywhere, Category = "Gun Stats")
		float bulletSpeed;
	UPROPERTY(EditAnywhere, Category = "Gun stats")
		int rpm;
	int shotsPerRound = 1;



	UPROPERTY(EditAnywhere, Category = "Controls")
	FKey FireKey;
	UPROPERTY(EditAnywhere, Category = "Controls")
	FKey ReloadKey;
	UPROPERTY(EditAnywhere, Category = "Controls")
	FKey OptionOneKey;
	UPROPERTY(EditAnywhere, Category = "Controls")
	FKey OptionTwoKey;

};
