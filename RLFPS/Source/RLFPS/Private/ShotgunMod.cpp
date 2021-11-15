// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotgunMod.h"
#include "NiagaraFunctionLibrary.h"

UShotgunMod::UShotgunMod()
{

}

UShotgunMod::~UShotgunMod()
{

}

void UShotgunMod::OnApply_Implementation()
{

}

void UShotgunMod::OnFire_Implementation(AGun* gun)
{
	FVector startingPoint = gun->GetActorLocation() + gun->MuzzleLocation * gun->GetActorForwardVector();

	for (int i = 0; i < stacks; i++)
	{
	
		if (gun->ammoRemaining <= 0)
		{
			return;
		}
		
		FVector vector(FMath::RandRange(-1,1), FMath::RandRange(-1, 1), FMath::RandRange(-1, 1));

		vector.Normalize();
		vector = vector * offsetMultiplier * ((float)(i + 1)/(float)(stacks + 1));
		
		FVector newPoint = startingPoint + vector;

		

		newPoint += gun->GetActorForwardVector();
		FVector dir = newPoint - startingPoint;
		dir;
		gun->SpawnRound(*gun->spawnParams, FVector::ZeroVector, dir);
	}
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), muzzleFlash, gun->GetActorLocation() + gun->MuzzleLocation * gun->GetActorForwardVector(), gun->GetActorRotation(), FVector(1));
	UE_LOG(LogTemp, Warning, TEXT("Calling Shotgun Mod On Fire"));
}

