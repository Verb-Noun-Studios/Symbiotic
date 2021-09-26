// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../FragPlayer.h"
#include "InputCoreTypes.h"
#include "Gun.generated.h"

UENUM()
enum class WeaponModType
{
	WM_INVALID		UMETA(DisplayName = "Invalid"),
	WM_ROF			UMETA(DisplayName = "Rate Of Fire"),
	WM_AMMO			UMETA(DisplayName = "Ammo"),
	WM_RELOAD		UMETA(DisplayName = "Reload"),
	WM_INVALID_LAST	UMETA(DisplayName = "Invalid Last"),
	

};

USTRUCT()
struct FWeaponModifier
{
	GENERATED_BODY()

	WeaponModType type;
	int stacks = 0;
};

UCLASS()
class RLFPS_API AGun : public AActor
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
	TArray<FWeaponModifier> Mods;

public:	
	// Sets default values for this actor's properties
	AGun();


	void Fire(float deltaTime);
	void SpawnRound();
	void Reload();
	bool GetFireKey();
	bool GetReloadKey();
	void AddMod(WeaponModType type);
	void UpdateCoreStats();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget = true))
	float MuzzleLocation;

	UPROPERTY(BlueprintReadWrite)
	bool firing = false;

	UPROPERTY(BlueprintReadWrite)
	int ammoRemaining;

	UPROPERTY(BlueprintReadWrite)
	bool reloading = false;
	 
	UPROPERTY(EditAnywhere, Category = "Game Stats")
	float defaultReloadTime = 5;
	UPROPERTY(EditAnywhere, Category = "Game Stats")
	int defaultAmmoCount = 10;
	UPROPERTY(EditAnywhere, Category = "Game Stats")
	int defaultRPM = 120;
	UPROPERTY(EditAnywhere, Category = "Game Stats")
	int defaultBulletSpeed = 120;
	



	UPROPERTY(EditAnywhere, Category = "Gun Stats")
	float reloadTime;
	UPROPERTY(EditAnywhere, Category = "Gun Stats")
	int ammoCount;
	UPROPERTY(EditAnywhere, Category = "Gun Stats")
	float bulletSpeed;
	UPROPERTY(EditAnywhere, Category = "Gun stats")
	int rpm;

	int shotsPerRound = 1;
	float elapsedTime = 0;

	UPROPERTY(EditAnywhere, Category = "Controls")
	FKey FireKey;
	UPROPERTY(EditAnywhere, Category = "Controls")
	FKey ReloadKey;

};
