// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveItem.h"
#include "GrappleItem.generated.h"

/**
 * 
 */
UCLASS()
class RLFPS_API UGrappleItem : public UActiveItem
{
	GENERATED_BODY()
	

public:
	UGrappleItem();
	~UGrappleItem();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> classToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxGrappleDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float minGrappleDistance;

	TSubclassOf<AActor> playerClass;

	virtual void OnActiveAbility_Implementation(AActor* gun) override;

};
