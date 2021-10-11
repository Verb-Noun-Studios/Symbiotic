// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmmoModBase.h"
#include "TestAmmoMod.generated.h"

/**
 * 
 */
UCLASS()
class RLFPS_API UTestAmmoMod : public UAmmoModBase
{
	GENERATED_BODY()
public:
	UTestAmmoMod();
	~UTestAmmoMod();

	void OnApply();
	void OnHit(AActor* actor);
};
