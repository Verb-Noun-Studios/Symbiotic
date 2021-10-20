// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModBase.generated.h"

UENUM()
enum class ModType : uint8
{
	MOD_GUN		UMETA(DisplayName = "Gun Mod"),
	MOD_AMMO		UMETA(DisplayName = "Ammo Mod"),
};


UENUM()
enum class ModSubType : uint8
{
	MOD_GUN_ROF				UMETA(DisplayName = "Gun Mod: ROF"),
	MOD_GUN_AMMO			UMETA(DisplayName = "Gun Mod: Ammo Capacity"),
	MOD_AMMO_EXPLODING		UMETA(DisplayName = "Ammo Mod: Exploading"),
	MOD_AMMO_RICOCHET		UMETA(DisplayName = "Ammo Mod: Ricocheting"),
};


UENUM()
enum class ModAdditionalAtrributes : uint8
{
	
	ATRIB_INCREASED_MAG			UMETA(DisplayName = "Magazine Increase"),
	ATRIB_RATE_OF_FIRE			UMETA(DisplayName = "Rate of Fire"),
	ATRIB_REDUCED_RELOAD_TIME	UMETA(DisplayName = "Reduced Reload Time"),

};


class ABullet;
class AGun;
/**
 * 
 */
UCLASS(Blueprintable)
class RLFPS_API UModBase : public UObject
{

	GENERATED_BODY()
public:
	UModBase();
	~UModBase();

	virtual void OnApply();
	virtual void OnSpawn(ABullet* bullet);
	virtual void OnFire(AGun* gun);
	virtual void OnHit(AActor* actor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ModType type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString infoText;

	int stacks = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ModAdditionalAtrributes> atribs;

	


};
