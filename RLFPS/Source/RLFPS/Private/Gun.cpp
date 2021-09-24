// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreMinimal.h"
#include "Gun.h"
#include "Bullet.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	ammoRemaining = ammoCount;
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	elapsedTime += DeltaTime;

	if (elapsedTime >= (60.0/(float)roundsPerMinute) && !reloading)
	{
		elapsedTime = 0;
		Fire();

		if (ammoRemaining == 0)
		{
			reloading = true;
		}
	}
	else if (reloading)
	{
		if (elapsedTime >= reloadTime)
		{
			reloading = false;
			elapsedTime = 0;
			ammoRemaining = ammoCount;
		}
	}
	
}

void AGun::Fire()
{

	UWorld* World = GetWorld();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	//spawn the bullets

	TArray<ABullet*> bullets;
	for (int i = 0; i < shotsPerRound; i++)
	{
		ABullet* bullet = World->SpawnActor<ABullet>(ProjectileClass, GetActorLocation() + MuzzleLocation * GetActorForwardVector(), GetActorRotation(), SpawnParams);
		if (bullet)
		{
			bullets.Add(bullet);
			bullets[i]->SetInitialSpeed(bulletSpeed);
			bullets[i]->SetInitialDirection(GetActorForwardVector());
			
		}
			
	}
	
	ammoRemaining--;
	
}

void AGun::Reload()
{

}

