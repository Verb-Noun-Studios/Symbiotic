// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StatusEffect.h"
#include "EnemySpawner.h"
#include "GruntCharacter.generated.h"

class UHealthComponent;

UCLASS()
class RLFPS_API AGruntCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGruntCharacter();

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UHealthComponent* HealthComponent;
	UPROPERTY(BlueprintReadOnly)
	TArray<UStatusEffect*> statusEffects;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AEnemySpawner* EnemySpawner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void AddEffect(UStatusEffect* effect);
	UFUNCTION(BlueprintCallable)
	void OnDeath();


};
