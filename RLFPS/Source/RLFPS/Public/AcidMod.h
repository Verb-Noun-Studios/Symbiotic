// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModBase.h"
#include "AcidMod.generated.h"

/**
 * 
 */

class AGun;

UCLASS()
class RLFPS_API UAcidMod : public UModBase
{
	GENERATED_BODY()
	

public:
	UAcidMod();
	~UAcidMod();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> acidActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float chance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float additionalchancePerStack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float additionalStrengthPerStack;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float damage = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float duration = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float interval = 0.3;



	void OnHit_Implementation(AActor* hitActor, UWorld* world);

};
