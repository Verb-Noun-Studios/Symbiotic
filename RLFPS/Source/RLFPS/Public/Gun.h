// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Gun.generated.h"

UENUM()
enum WeaponModType
{
	RATE_OF_FIRE

};

USTRUCT()
struct FWeaponModifier
{

	GENERATED_BODY()
};

UCLASS()
class RLFPS_API AGun : public AActor
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;
	
public:	
	// Sets default values for this actor's properties
	AGun();
	void Fire();
	void Reload();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget = true))
	float MuzzleLocation;

	float elapsedTime = 0;
	int roundsPerMinute = 200;
	int shotsPerRound = 1;

	float bulletSpeed = 500;


	float ammoCount = 35;
	float ammoRemaining;
	bool reloading = false;
	float reloadTime = 5;
	
};
