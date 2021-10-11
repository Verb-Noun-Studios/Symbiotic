// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModBase.h"
#include "AmmoModBase.generated.h"


UENUM()
enum class AmmoModType : uint8
{
	MOD_AMMO_EXPLODING		UMETA(DisplayName = "Ammo Mod: Exploading"),
	MOD_AMMO_RICOCHET		UMETA(DisplayName = "Ammo Mod: Ricocheting"),
};


/**
 * 
 */
UCLASS()
class RLFPS_API UAmmoModBase : public UModBase
{
	GENERATED_BODY()

public:
	AmmoModType ammoModType;
	UAmmoModBase();
	~UAmmoModBase();
	void OnApply();
	virtual void OnHit(AActor* actor);
	

	

};
