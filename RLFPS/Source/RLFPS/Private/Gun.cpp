// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include"IncreasedMagMod.h"
#include "TestAmmoMod.h"
#include "CoreMinimal.h"
#include "UObject/UObjectGlobals.h"
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

	UTestAmmoMod* mod = NewObject<UTestAmmoMod>();

	AddAmmoMod(mod);
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
			firing = false;
			//Reload();
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
	else if (GetFireKey() && ammoRemaining > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Calling Fire"));
		Fire(DeltaTime);
	}
	else
	{
		firing = false;
	}

	if (ammoRemaining <= 0 && !reloading)
	{
		firing = false;
		//Reload();
		reloading = true;
	}

	//if (readyToLevelUp)
	//{
	//	if (GetOptionOneKey())
	//	{
	//		//LevelUp(ModOptions[0]);
	//	}
	//	else if (GetOptionTwoKey())
	//	{
	//		//LevelUp(ModOptions[1]);
	//	}
	//}
	
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
		firing = true;
	}

	//UE_LOG(LogTemp, Warning, TEXT("Ammo Remaining: %d"), ammoRemaining);

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
			bullets[i]->SetGun(this);

		}

	}
}


void AGun::AddGunMod(UGunModBase* newMod)
{
	for (int i = 0; i < gunMods.Num(); i++)
	{
		if (newMod->gunModType == gunMods[i]->gunModType)
		{
			gunMods[i]->stacks++;
			//mod->OnApply(reloadTime, ammoCount, bulletSpeed, rpm);
			return;
		}
	}
	
	int index = gunMods.Add(newMod);
	//gunMods[index]->OnApply(reloadTime, ammoCount, bulletSpeed, rpm);

	UE_LOG(LogTemp, Warning, TEXT("Ammo Count: %d"), ammoCount);
	UE_LOG(LogTemp, Warning, TEXT("RPM: %d"), rpm);
	UE_LOG(LogTemp, Warning, TEXT("Reload Time: %f"), reloadTime);

}

void AGun::AddAmmoMod(UAmmoModBase* newMod)
{
	for (int i= 0; i < ammoMods.Num(); i++)
	{
		if (newMod->ammoModType == ammoMods[i]->ammoModType)
		{
			ammoMods[i]->stacks++;
			ammoMods[i]->OnApply();
			return;
		}
	}

	ammoMods.Add(newMod);
	ammoMods[ammoMods.Num()-1]->OnApply();
	
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

bool AGun::GetOptionOneKey()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool reloadState = playerController->IsInputKeyDown(OptionOneKey);

	return reloadState;

}

bool AGun::GetOptionTwoKey()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool reloadState = playerController->IsInputKeyDown(OptionTwoKey);

	return reloadState;

}


void AGun::OnHitCallback(AActor* actor)
{
	if (ammoMods.Num()){
		for (int i = 0; i < ammoMods.Num(); i ++)
		{
			ammoMods[i]->OnHit(actor);
		}
	}

	
}

