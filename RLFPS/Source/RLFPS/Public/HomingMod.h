// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModBase.h"
#include "HomingMod.generated.h"

/**
 * 
 */
UCLASS()
class RLFPS_API UHomingMod : public UModBase
{
	GENERATED_BODY()
	
public:
	UHomingMod();
	~UHomingMod();
	void OnSpawn_Implementation(ABullet* bullet);
};
