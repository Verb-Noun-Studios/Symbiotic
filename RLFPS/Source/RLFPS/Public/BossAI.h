// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossAI.generated.h"

class UHealthComponent;

UCLASS()
class RLFPS_API ABossAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossAI();

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UHealthComponent* HealthComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mChargeSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mShieldDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mMeleeRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mChargeRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mChargeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mChargeStartupTime;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mMeleeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mRangedDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mChargeDamage;

	float cTimer = 0;
	float mTimer= 0;
	float rTimer = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mMeleeRecharge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mRangedRecharge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mHealthScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mDamageScale;


	UFUNCTION(BlueprintCallable)
	int ChooseAction(float healthThreshold);

	UFUNCTION(BlueprintCallable)
	float update(FVector playerLoc, FVector bossLoc, float dt);

	UFUNCTION(BlueprintCallable)
	void resetTimer(int num);

	UFUNCTION(BlueprintCallable)
	void calculateScale(int num);

private:
	float distanceToPlayer;
	FVector directionToPlayer;
};
