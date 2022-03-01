// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModBase.h"
#include "ActiveItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RLFPS_API UActiveItem : public UModBase
{
	GENERATED_BODY()

public:
	UActiveItem();
	~UActiveItem();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int requiredKillCount = 15;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int currentKillCount = 15;

	UFUNCTION(BlueprintNativeEvent)
	void OnActiveAbility(AActor* gun);

	

};
