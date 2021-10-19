// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
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
	Damage = defaultDamage;

	//set RPM
	rpm = defaultRPM;

	//set reload time
	reloadTime = defaultReloadTime;

	//set bullet speed
	bulletSpeed = defaultBulletSpeed;

	FActorSpawnParameters* SpawnParams = new FActorSpawnParameters;
	SpawnParams->Owner = this;
	SpawnParams->Instigator = GetInstigator();
	SpawnParams->SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawnParams = SpawnParams;


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

	if (readyToLevelUp)
	{
		if (GetOptionOneKey())
		{
			LevelUp(ModOptions[0]);
		}
		else if (GetOptionTwoKey())
		{
			LevelUp(ModOptions[1]);
		}
	}
	
}

void AGun::Fire(float deltaTime)
{

	elapsedTime += deltaTime;
	firing = false;
	if (elapsedTime >= (60.0 / rpm))
	{

		elapsedTime = 0;
		SpawnRound(*spawnParams);
	;

		for (UModBase* mod : mods)
		{
			mod->OnFire(this);
		}

		ammoRemaining--;
		firing = true;
	}


	
	//UE_LOG(LogTemp, Warning, TEXT("Ammo Remaining: %d"), ammoRemaining);

}

void AGun::SpawnRound(FActorSpawnParameters SpawnParams)
{
	UWorld* World = GetWorld();
	
	ABullet* bullet = World->SpawnActor<ABullet>(ProjectileClass, (GetActorLocation() + MuzzleLocation * GetActorForwardVector()), GetActorRotation(), SpawnParams);

	if (bullet)
	{
		bullet->SetInitialSpeed(bulletSpeed);

		FVector dir = GetActorForwardVector();
		dir.Normalize();
		bullet->SetInitialDirection(dir);
		bullet->SetGun(this);

		for (UModBase* mod : mods)
		{
			mod->OnSpawn(bullet);
		}
	}
	
}

void AGun::SpawnRound(FActorSpawnParameters SpawnParams, FVector offset, FVector dir)
{
	UWorld* World = GetWorld();

	ABullet* bullet = World->SpawnActor<ABullet>(ProjectileClass, (GetActorLocation() + MuzzleLocation * GetActorForwardVector()) + offset, GetActorRotation(), SpawnParams);

	if (bullet)
	{
		bullet->SetInitialSpeed(bulletSpeed);
		bullet->SetInitialDirection(dir);
		bullet->SetGun(this);

		for (UModBase* mod : mods)
		{
			mod->OnSpawn(bullet);
		}
	}

}


void AGun::AddMod(UModBase* mod)
{
	for (int i = 0; i < mods.Num(); i++)
	{
		if (mod->GetClass() == mods[i]->GetClass())
		{
			mods[i]->stacks++;
			UpdateCoreStats();
			return;
		}
	}

	mods.Add(mod);
	UpdateCoreStats();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *mod->GetClass()->GetFullName() );
	return;
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
	if (mods.Num()){
		for (int i = 0; i < mods.Num(); i ++)
		{
			mods[i]->OnHit(actor);
		}
	}

	
}




void AGun::GainEXP(int exp)
{
	if (readyToLevelUp)
	{
		currentEXP += exp;
		return;
	}

	currentEXP += exp;

	if (currentEXP > expToNextLevel)
	{
		readyToLevelUp = true;
		ModOptions.Empty();
		ModOptions = GetNewModOptions();
		currentEXP = currentEXP - expToNextLevel;
	}
}


float AGun::GetLevelPercentage()
{
	return (float)currentEXP / (float)expToNextLevel;
}

TArray<UModBase*> AGun::GetNewModOptions()
{
	
	int randOne = FMath::RandHelper(allMods.Num());

	UModBase* modOne = NewObject<UModBase>((UObject*)this, allMods[randOne]);;

	int randTwo = FMath::RandHelper(allMods.Num());


	UModBase* modTwo = NewObject<UModBase>((UObject*)this, allMods[randTwo]);
	
	return TArray<UModBase*>{modOne, modTwo};

}

TArray<UModBase*> AGun::GetModOptions()
{
	TArray<UModBase*> options;
	for (UModBase* type : ModOptions)
	{
		options.Add(type);
	}
	return ModOptions;
}


void AGun::LevelUp(UModBase* newModType)
{
	AddMod(newModType);
	//AddMod(newModType);

	expToNextLevel *= 2;
	if (GetLevelPercentage() != 1)
	{
		readyToLevelUp = false;
	}

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("LEVEL UP!"), true, FVector2D(2, 2));

}


void AGun::UpdateCoreStats()
{
	int ammoModStacks = 0;
	int rofModStacks = 0;
	int reloadModStacks = 0;

	for (int i = 0; i < mods.Num(); i++)
	{
		for (ModAdditionalAtrributes atrib : mods[i]->atribs)
		{
			switch (atrib)
			{

			case ModAdditionalAtrributes::ATRIB_INCREASED_MAG:
				ammoModStacks += mods[i]->stacks;
				break;
			case ModAdditionalAtrributes::ATRIB_RATE_OF_FIRE:
				rofModStacks += mods[i]->stacks;
				break;
			case ModAdditionalAtrributes::ATRIB_REDUCED_RELOAD_TIME:
				reloadModStacks += mods[i]->stacks;
			default:
				break;
			}

		}

		
	}


	if (ammoModStacks > 0)
	{
		ammoCount = defaultAmmoCount * ammoModStacks * 1.5;

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
