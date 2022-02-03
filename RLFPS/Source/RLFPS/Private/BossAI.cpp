// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAI.h"

// Sets default values
ABossAI::ABossAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABossAI::BeginPlay()
{
	Super::BeginPlay();
	
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

int ABossAI::ChooseAction()
{
	if (distanceToPlayer <= meleeRange && mTimer <= 0)
	{
		mTimer = meleeRecharge;
		return 1;
	}
	else if(distanceToPlayer > meleeRange)
	{
		if (cTimer >= chargeTime)
		{
			cTimer = 0.0f;
			return 3;
		}

		if (rTimer <= 0)
		{
			rTimer = rangedRecharge;
			return 2;
		}
	}
	return 0;
		
}

float ABossAI::update(FVector playerLoc, FVector bossLoc, float dt)
{
	distanceToPlayer = FVector::Dist(playerLoc, bossLoc)/100;

	if (distanceToPlayer > chargeRange)
		cTimer += dt;
	else
		cTimer = 0.0;

	if (mTimer > 0.0)
		mTimer -= dt;
	if (rTimer > 0.0)
		rTimer -= dt;

	return distanceToPlayer;
}

FVector ABossAI::moveTo(FVector playerLoc, FVector bossLoc, float dt)
{
	directionToPlayer = playerLoc - bossLoc;
	return directionToPlayer * dt;
}
