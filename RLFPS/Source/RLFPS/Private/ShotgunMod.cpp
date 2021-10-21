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
	FVector startingPoint = gun->GetActorLocation() + gun->MuzzleLocation * gun->GetActorForwardVector();

	for (int i = 0; i < stacks; i++)
	{
		FVector vector(FMath::RandRange(-1,1), FMath::RandRange(-1, 1), FMath::RandRange(-1, 1));

		vector.Normalize();
		vector = vector * offsetMultiplier * ((float)(i + 1)/(float)(stacks + 1));
		
		FVector newPoint = startingPoint + vector;

		

		newPoint += gun->GetActorForwardVector();
		FVector dir = newPoint - startingPoint;
		dir;
		gun->SpawnRound(*gun->spawnParams, FVector::ZeroVector, dir);
	}

	UE_LOG(LogTemp, Warning, TEXT("Calling Shotgun Mod On Fire"));
}

void UShotgunMod::OnHit(AActor* actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Shotgun Mod On Apply"));
}