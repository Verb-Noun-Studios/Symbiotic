// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotgunMod.h"

UShotgunMod::UShotgunMod()
{

}

UShotgunMod::~UShotgunMod()
{

}

void UShotgunMod::OnApply()
{

}

void UShotgunMod::OnFire(AGun* gun)
{
	for (int i = 0; i < stacks; i++)
	{
		FVector vector(FMath::Rand(), FMath::Rand(), FMath::Rand());

		vector.Normalize();
		vector = vector * offsetMultiplier;
		gun->SpawnRound(*gun->spawnParams, vector);
	}
}

void UShotgunMod::OnHit(AActor* actor)
{

}