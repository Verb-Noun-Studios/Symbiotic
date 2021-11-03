// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModBase.h"
#include "ReloadknockBackMod.generated.h"

/**
 * 
 */
UCLASS()
class RLFPS_API UReloadKnockBackMod : public UModBase
{
	GENERATED_BODY()

public:
	UReloadKnockBackMod();
	~UReloadKnockBackMod();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> classToFind;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> playerClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float additionalRangePerStack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float additionalStrengthPerStack;


	void OnReload_Implementation(AActor* player);
};
