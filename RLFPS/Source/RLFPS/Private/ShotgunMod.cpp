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
		FVector startingPoint = gun->GetActorLocation() + gun->MuzzleLocation * gun->GetActorForwardVector();
		FVector newPoint = startingPoint + vector;

		

		newPoint += gun->GetActorForwardVector();
		FVector dir = newPoint - startingPoint;
		dir.Normalize();
		gun->SpawnRound(*gun->spawnParams, FVector::ZeroVector, dir);
	}

	UE_LOG(LogTemp, Warning, TEXT("Calling Shotgun Mod On Fire"));
}

void UShotgunMod::OnHit(AActor* actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Shotgun Mod On Apply"));
}