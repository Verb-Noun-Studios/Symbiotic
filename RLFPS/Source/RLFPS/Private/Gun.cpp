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

	//set ammo
	ammoCount = defaultAmmoCount;
	ammoRemaining = ammoCount;
	
	//set RPM
	rpm = defaultRPM;

	//set reload time
	reloadTime = defaultReloadTime;

	//set bullet speed
	bulletSpeed = defaultBulletSpeed;

}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	elapsedTime += DeltaTime;
	
	if (!reloading)
	{
		reloading = GetReloadKey();
		if (reloading)
		{
			Reload();
		}
		
	}
	
	if (reloading)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 0.10f, FColor::Yellow, TEXT("Reloading"));
		if (elapsedTime >= reloadTime)
		{
			reloading = false;
			elapsedTime = 0;
			ammoRemaining = ammoCount;
			UE_LOG(LogTemp, Warning, TEXT("Finished Reloading"));
		}
	}
	else if(GetFireKey() && ammoRemaining > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Calling Fire"));
		Fire(DeltaTime);
	}

	if(ammoRemaining <= 0 && !reloading)
	{
		Reload();
		reloading = true;
	}
	
	
}

void AGun::Fire(float deltaTime)
{
	
	elapsedTime += deltaTime;
	firing = false;
	if (elapsedTime >= (60.0 / rpm))
	{
	
		elapsedTime = 0;
		SpawnRound();
		ammoRemaining--;
	}

	//UE_LOG(LogTemp, Warning, TEXT("Ammo Remaining: %d"), ammoRemaining);
	
}

void AGun::Reload()
{
	//trigger animations here
}

void AGun::SpawnRound()
{
	firing = true;
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

void AGun::AddMod(int modNum)
{

	for (int i = 0; i < Mods.Num(); i++)
	{

		if (Mods[i].type == (WeaponModType)modNum)
		{
			Mods[i].stacks++;
			UpdateCoreStats();
			return;
		}
	}

	
	FWeaponModifier newMod = FWeaponModifier();
	newMod.type = (WeaponModType)modNum;
	newMod.stacks = 1;
	Mods.Add(newMod);

	UpdateCoreStats();

	return;
}


void AGun::GainEXP(int exp)
{
	currentEXP += exp;

	if (currentEXP > expToNextLevel)
	{
		LevelUp();
	}
}


void AGun::LevelUp()
{
	int mod = FMath::RandRange(1, 3);

	AddMod(mod);

	expToNextLevel *= 2;

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("LEVEL UP!"), true, FVector2D(2,2));


	switch (mod)
	{
	case 1:
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Adding Rate of Fire Mod"), false, FVector2D(2, 2));
		break;
	case 2:
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Adding Ammo Mod"), false, FVector2D(2, 2));
		break;
	case 3:
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Adding Reload Mod"), false, FVector2D(2, 2));
		break;
	}

}


void AGun::UpdateCoreStats()
{
	int ammoModStacks = 0;
	int rofModStacks = 0;
	int reloadModStacks = 0;

	for (int i = 0; i < Mods.Num(); i++)
	{

		if (Mods[i].type == WeaponModType::WM_AMMO)
		{
			ammoModStacks += Mods[i].stacks;
		}

		if (Mods[i].type == WeaponModType::WM_ROF)
		{
			rofModStacks += Mods[i].stacks;
		}
		if (Mods[i].type == WeaponModType::WM_RELOAD)
		{
			reloadModStacks += Mods[i].stacks;
		}
	}
	if (ammoModStacks > 0)
	{
		ammoCount = defaultAmmoCount * 2 * ammoModStacks;

	}
	
	
	rpm = defaultRPM;
	for (int j = 0; j < rofModStacks; j++)
	{
		rpm += rpm;
	}

	reloadTime = defaultReloadTime;
	for (int j = 0; j < reloadModStacks; j++)
	{
		reloadTime *= 0.8;
	}

	bulletSpeed = defaultBulletSpeed;


	UE_LOG(LogTemp, Warning, TEXT("Ammo Count: %d"), ammoCount);
	UE_LOG(LogTemp, Warning, TEXT("RPM: %d"), rpm);
	UE_LOG(LogTemp, Warning, TEXT("Reload Time: %f"), reloadTime);

}
