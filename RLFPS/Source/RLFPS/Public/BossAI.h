// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossAI.generated.h"

UCLASS()
class RLFPS_API ABossAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float walkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float chargeSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int currentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float shieldDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float meleeRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float chargeRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float chargeTime;

	float cTimer = 0;
	float mTimer;
	float rTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float meleeRecharge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rangedRecharge;

	UFUNCTION(BlueprintCallable)
	int ChooseAction();

	UFUNCTION(BlueprintCallable)
	float update(FVector playerLoc, FVector bossLoc, float dt);

	UFUNCTION(BlueprintCallable)
	FVector moveTo(FVector playerLoc, FVector bossLoc, float dt);

private:
	float distanceToPlayer;
	FVector directionToPlayer;
};
