// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
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
	
	if (!reloading)
	{
		reloading = GetReloadKey();
	}
	
	if (reloading)
	{
		if (elapsedTime >= reloadTime)
		{
			reloading = false;
			elapsedTime = 0;
			ammoRemaining = ammoCount;
		}
	}
	else if(GetFireKey() && ammoRemaining > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Calling Fire"));
		Fire(DeltaTime);
	}


	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool makeNewMod = playerController->IsInputKeyDown(EKeys::SpaceBar);
	
	if (makeNewMod)
	{
		AddMod(WeaponModType::WM_ROF);
		UE_LOG(LogTemp, Warning, TEXT("Adding Mod"));
	}
	
}

void AGun::Fire(float deltaTime)
{
	int rofModStacks = 0;
	

	for (int i = 0; i < Mods.Num(); i++)
	{
		if (Mods[i].type == WeaponModType::WM_ROF)
		{
			rofModStacks += Mods[i].stacks;
		}
	}

	
	UE_LOG(LogTemp, Warning, TEXT("finished counting mods"));


	int additionalRPM = (int)(roundsPerMinute * rofModStacks);


	elapsedTime += deltaTime;

	if (elapsedTime >= (60.0 / ((float)roundsPerMinute + additionalRPM)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning round"));
		elapsedTime = 0;
		SpawnRound();
	}
	
	ammoRemaining--;

	
	
}

void AGun::Reload()
{

}

void AGun::SpawnRound()
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
}

bool AGun::GetFireKey()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool fireState = playerController->IsInputKeyDown(FireKey);
	
	return fireState;
}

bool AGun::GetReloadKey()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool reloadState = playerController->IsInputKeyDown(ReloadKey);
	
	return reloadState;
	
}

void AGun::AddMod(WeaponModType type)
{

	for (int i = 0; i < Mods.Num(); i++)
	{

		if (Mods[i].type == type)
		{
			Mods[i].stacks++;
			return;
		}
	}

	
	FWeaponModifier newMod = FWeaponModifier();
	newMod.type = type;
	newMod.stacks = 1;
	Mods.Add(newMod);
	return;
}

