// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAI.h"
#include "HealthComponent.h"

// Sets default values
ABossAI::ABossAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Defragr Health Component"));

}

// Called when the game starts or when spawned
void ABossAI::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->currentHealth = mMaxHealth;
	HealthComponent->DefaultHealth = mMaxHealth;
	sTimer = mSummonTime;
}

// Called every frame
void ABossAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABossAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int ABossAI::ChooseAction(float healthThreshold)
{
	
	if (HealthComponent->currentHealth < healthThreshold)
	{
		return 4;
	}
	
	if (sTimer <= 0)
	{
		return 5;
	}

	if (distanceToPlayer <= mMeleeRange && mTimer <= 0)
	{
		return 1;
	}
	else if(distanceToPlayer > mMeleeRange)
	{
		if (cTimer >= mChargeTime && !hasCharged)
		{
			cTimer = 0.0f;
			hasCharged = true;
			return 3;
		}
		else if (cTimer >= mChargeTime && hasCharged)
		{
			cTimer = 0.0f;
			hasCharged = false;
			return 6;
		}

		if (rTimer <= 0)
		{
			return 2;
		}
	}
	return 0;
		
}

float ABossAI::update(FVector playerLoc, FVector bossLoc, float dt)
{
	distanceToPlayer = FVector::Dist(playerLoc, bossLoc)/100;

	if (distanceToPlayer > mChargeRange)
		cTimer += dt;
	else
		cTimer = 0.0;

	if (mTimer > 0.0)
		mTimer -= dt;
	if (rTimer > 0.0)
		rTimer -= dt;

	if (sTimer > 0)
	{
		sTimer -= dt;
	}
	return distanceToPlayer;
}


void ABossAI::resetTimer(int num)
{
	switch (num)
	{
	case 0:
		mTimer = mMeleeRecharge;
		break;
	case 1:
		rTimer = mRangedRecharge;
		break;
	case 2:
		sTimer = mSummonTime;
		break;
	}
}

float ABossAI::calculateScale(int num)
{
	float damagePercent = (mDamageScale * num)/100;
	float healthPercent = (mHealthScale * num)/100;

	mMaxHealth += healthPercent * mMaxHealth;
	mRangedDamage += damagePercent * mRangedDamage;
	mChargeDamage += damagePercent * mChargeDamage;
	mMeleeDamage += damagePercent * mMeleeDamage;

	return (float)mMaxHealth;
}

