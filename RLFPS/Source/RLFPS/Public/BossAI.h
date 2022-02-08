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

	float cTimer = 0;
	float mTimer;
	float rTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mMeleeRecharge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mRangedRecharge;

	UFUNCTION(BlueprintCallable)
	int ChooseAction();

	UFUNCTION(BlueprintCallable)
	float update(FVector playerLoc, FVector bossLoc, float dt);

	UFUNCTION(BlueprintCallable)
	FVector moveTo(FVector playerLoc, FVector bossLoc, float dt);

	UFUNCTION(BlueprintCallable)
	void resetTimer(int num);

private:
	float distanceToPlayer;
	FVector directionToPlayer;
};
