// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModBase.h"
#include "IncreasedMagMod.generated.h"

/**
 * 
 */
UCLASS()
class RLFPS_API UIncreasedMagMod : public UModBase
{
	GENERATED_BODY()

	

public:
	UIncreasedMagMod();
	~UIncreasedMagMod();
	void OnApply();
	void OnHit(AActor* actor);
};
