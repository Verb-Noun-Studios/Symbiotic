// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModBase.h"
#include "GunModBase.generated.h"


UENUM()
enum class GunModType : uint8
{
	MOD_GUN_ROF			UMETA(DisplayName = "Gun Mod: ROF"),
	MOD_GUN_AMMO		UMETA(DisplayName = "Gun Mod: Ammo Capacity"),
};



/**
 * 
 */
UCLASS()
class RLFPS_API UGunModBase : public UModBase
{
	GENERATED_BODY()
	
public:

	UGunModBase();
	~UGunModBase();

	ModType type = ModType::MOD_GUN;
	GunModType gunModType;


	//virtual void OnApply(float& reloadTime, int& ammoCount, float& bulletSpeed, int& rpm);
		
};
