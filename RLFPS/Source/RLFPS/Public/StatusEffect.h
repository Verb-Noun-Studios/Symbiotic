// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatusEffect.generated.h"

class AGruntCharacter;

/**
 * 
 */
UCLASS(Blueprintable)
class RLFPS_API UStatusEffect : public UObject
{
	GENERATED_BODY()


public:

	UStatusEffect();
	~UStatusEffect();


	/********** VARIABLES *************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* icon;

	UPROPERTY(BlueprintReadOnly)
	int stacks = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float duration = 10;

	UPROPERTY(BlueprintReadOnly)
	float timeRemaining;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float timeBetweenTicks = 1;

	UPROPERTY(BlueprintReadWrite)
	float timeSinceLastTick = 0;


	bool dead = false;
	AGruntCharacter* owner;

	UFUNCTION(BlueprintNativeEvent)
	void OnTick(AActor* actor, float deltaTime);

	UFUNCTION(BlueprintNativeEvent)
	void OnDestroy(AActor* actor);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnStart(AActor* actor);

	UFUNCTION(BlueprintCallable)
	AActor* GetActorOfClass_Internal(TSubclassOf<AActor> actorClass);

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetActorsOfClass_Internal(TSubclassOf<AActor> actorClass);

	UFUNCTION(BlueprintCallable)
	UWorld* GetWorld_Internal();

	
	
};
