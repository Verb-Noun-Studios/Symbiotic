// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModBase.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "ReloadBomb.generated.h"


/**
 * 
 */
UCLASS()
class RLFPS_API UReloadBombMod : public UModBase
{
	GENERATED_BODY()
	
		
		

public:
	UReloadBombMod();
	~UReloadBombMod();
	
	void OnReload_Implementation(AActor* actor);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AActor> classToFind;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> playerClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float additionalRangePerStack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float additionalDamagePerStack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* reloadBombEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float particleSystemScale;


};
