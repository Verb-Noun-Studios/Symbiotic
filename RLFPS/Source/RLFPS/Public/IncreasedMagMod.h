// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunModBase.h"
#include "IncreasedMagMod.generated.h"

/**
 * 
 */
UCLASS()
class RLFPS_API UIncreasedMagMod : public UGunModBase
{
	GENERATED_BODY()

	

public:
	UIncreasedMagMod();
	~UIncreasedMagMod();


	GunModType gunModType = GunModType::MOD_GUN_AMMO;
	void OnApply();
};
