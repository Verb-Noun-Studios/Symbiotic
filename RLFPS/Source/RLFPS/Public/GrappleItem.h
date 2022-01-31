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

	void OnActiveItem_Implementation(AActor* actor);
};
