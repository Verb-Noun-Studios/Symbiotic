// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "UObject/UObjectGlobals.h"
#include "Camera/CameraComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleEmitter.h"
#include "NiagaraFunctionLibrary.h"
#include "Bullet.h"
#include "SaveControllerSubsystem.h"
#include "../FragPlayer.h"
#include "HealthComponent.h"



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

	{
		// load mods if there are some in from the mods list
		USaveControllerSubsystem* subsystem = GetGameInstance()->GetSubsystem<USaveControllerSubsystem>();
		subsystem->LoadGunData(this);
		UpdateCoreStats();
	}
	curWeights = weights;
	player = (AFragPlayer*)UGameplayStatics::GetActorOfClass(GetWorld(), AFragPlayer::StaticClass());
}

//called whenever this actor is being removed 
void AGun::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	// save mods to subsystem before unload
	if (EndPlayReason == EEndPlayReason::Destroyed) {
		USaveControllerSubsystem* subsystem = GetGameInstance()->GetSubsystem<USaveControllerSubsystem>();
		subsystem->SaveGunData(this);
	}
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	elapsedTime += DeltaTime;

	if (GetActiveKey() && activeItem)
	{
		if (activeItem->currentKillCount >= activeItem->requiredKillCount)
		{
			
			activeItem->OnActiveAbility(this);
			activeItem->OnActiveAbility_Implementation(this);
			activeItem->BeginRecharge();
			//GEngine->AddOnScreenDebugMessage(-1, 0.10f, FColor::Yellow, TEXT("Calling active Item"));
			
		}

		//UE_LOG(LogTemp, Warning, TEXT("Current Kills: %d   VS Required Kills: %d"), activeItem->currentKillCount, activeItem->requiredKillCount);
	}

	if (!reloading)
	{
		reloading = GetReloadKey();
		if (reloading)
		{
			elapsedTime = 0;
			firing = false;
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
		Reload();
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

	//elapsedTime += deltaTime;
	firing = false;
	if (elapsedTime >= (60.0 / rpm))
	{

		elapsedTime = 0;
		SpawnRound(*spawnParams);
	;

		for (UModBase* mod : mods)
		{
			mod->OnFire(this);
			mod->OnFire_Implementation(this);
		}

		
		firing = true;
	}


	
	//UE_LOG(LogTemp, Warning, TEXT("Ammo Remaining: %d"), ammoRemaining);

}

void AGun::Reload()
{
	for (UModBase* mod : mods)
	{
		mod->OnReload(this);
		mod->OnReload_Implementation(this);
	}
}

void AGun::SpawnRound(FActorSpawnParameters SpawnParams)
{
	UWorld* World = GetWorld();
	
	ABullet* bullet = World->SpawnActor<ABullet>(ProjectileClass, (GetActorLocation() + MuzzleLocation * GetActorForwardVector()), GetActorRotation(), SpawnParams);

	if (bullet)
	{
		bullet->SetInitialSpeed(bulletSpeed);

		FVector dir = RaycastFromCamera() - (GetActorLocation());

		
		dir.Normalize();
		bullet->SetInitialDirection(dir);
		bullet->SetGun(this);

		for (UModBase* mod : mods)
		{
			mod->OnSpawn(bullet);
			mod->OnSpawn_Implementation(bullet);
		}

		for (UModBase* mod : mods)
		{
			mod->OnUpdateBulletVFX(bullet);
			mod->OnUpdateBulletVFX_Implementation(bullet);
		}

		bullet->UpdateVFX();
		
	}

	//ammoRemaining--;

	PlayMuzzleFlashFX();


	
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
			mod->OnSpawn_Implementation(bullet);
		}


		for (UModBase* mod : mods)
		{
			mod->OnUpdateBulletVFX(bullet);
			mod->OnUpdateBulletVFX_Implementation(bullet);
		}
		
		bullet->UpdateVFX();
	}

	//ammoRemaining--;
	
}

void AGun::AddMod(TSubclassOf<UModBase> modType) {
	if (modType == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Called AddMod with NULL Class"));
		return;
	}
	UModBase* newMod = NewObject<UModBase>(this, modType);
	AddMod(newMod);
}

void AGun::AddMod(UModBase* mod) {
	if (mod == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Called AddMod with NULL Object"));
		return;
	}
	for (int i = 0; i < mods.Num(); i++)
	{
		if (mod->GetClass() == mods[i]->GetClass())
		{
			mods[i]->stacks++;
			mods[i]->OnApply(player);
			mod->ConditionalBeginDestroy();
			UpdateCoreStats();
			return;
		}
	}

	mods.Add(mod);
	mod->OnApply(player);
	UpdateCoreStats();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *mod->GetClass()->GetFullName() );
	return;
}


void AGun::ReplaceActiveItem(UActiveItem* newItem)
{
	if (activeItem)
	{

		activeItem->ConditionalBeginDestroy();
	
	}
	
	activeItem = newItem;
}




bool AGun::GetFireKey()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool fireState;
	
	if (!LeftHanded)
	{
		fireState = playerController->IsInputKeyDown(RightFireKey);
	}
	else
	{
		fireState = playerController->IsInputKeyDown(LeftFireKey);
	}

	
	
	return fireState;
}

bool AGun::GetReloadKey()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool reloadState;
	if (!LeftHanded)
	{
		reloadState = playerController->IsInputKeyDown(RightReloadKey);
	}
	else
	{
		reloadState = playerController->IsInputKeyDown(LeftReloadKey);
	}
	 
	
	return reloadState;
	
}

bool AGun::GetOptionOneKey()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool keyState;

	if (!LeftHanded)
	{
		keyState = playerController->IsInputKeyDown(RightOptionOneKey);
	}
	else
	{
		keyState = playerController->IsInputKeyDown(LeftOptionOneKey);
	}

	return keyState;

}

bool AGun::GetOptionTwoKey()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool keyState;

	if (!LeftHanded)
	{
		keyState = playerController->IsInputKeyDown(RightOptionTwoKey);
	}
	else
	{
		keyState = playerController->IsInputKeyDown(LeftOptionTwoKey);
	}

	return keyState;

}

bool AGun::GetActiveKey()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool keyState;

	if (!LeftHanded)
	{
		keyState = playerController->IsInputKeyDown(RightActiveKey);
	}
	else
	{
		keyState = playerController->IsInputKeyDown(LeftActiveKey);
	}

	return keyState;

}


void AGun::OnHitCallback(AActor* actor)
{
	if (mods.Num()){
		for (int i = 0; i < mods.Num(); i ++)
		{
			mods[i]->OnHit(actor, GetWorld());
			mods[i]->OnHit_Implementation(actor, GetWorld());
		}
	}
}

void AGun::OnHitCallbackWithSkip(AActor* actor, FName name)
{
	if (mods.Num())
	{
		for (int i = 0; i < mods.Num(); i++)
		{
			if (mods[i]->name != name)
			{
				mods[i]->OnHit(actor, GetWorld());
				mods[i]->OnHit_Implementation(actor, GetWorld());
			}
			
		}
	}


}


void AGun::GainEXP(int exp)
{
	totalEXP += exp;

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
		TriggerUpgradeUI();
		currentEXP = currentEXP - expToNextLevel;
	}

	if (activeItem)
	{
		if(activeItem->currentKillCount < activeItem->requiredKillCount)
			activeItem->currentKillCount++;

	}
}


float AGun::GetLevelPercentage()
{
	return (float)currentEXP / (float)expToNextLevel;
}

TArray<UModBase*> AGun::GetModOptions()
{
	//TArray<UModBase*> options;
	//for (UModBase* type : ModOptions)
	//{
	//	options.Add(type);
	//}
	return ModOptions;
}

TArray<UModBase*> AGun::GetNewModOptions()
{
	
	int rarity = 0;

	int sum_of_weight = 0;
	for (int i = 0; i < 4; i++) {
		sum_of_weight += curWeights[i];
	}
	int rnd = FMath::RandRange(0, sum_of_weight);
	for (int i = 0; i < 4; i++) {
		if (rnd < curWeights[i])
		{
			rarity = i;
			break;
		}
		rnd -= curWeights[i];
	}

	UModBase* modOne = nullptr;
	int randOne;
	switch (rarity)
	{
	case 0:
		randOne = FMath::RandHelper(modsCommon.Num());
		modOne = NewObject<UModBase>((UObject*)this, modsCommon[randOne]);;
		break;
	case 1:
		randOne = FMath::RandHelper(modsUncommon.Num());
		modOne = NewObject<UModBase>((UObject*)this, modsUncommon[randOne]);;
		break;
	case 2:
		randOne = FMath::RandHelper(modsRare.Num());
		modOne = NewObject<UModBase>((UObject*)this, modsRare[randOne]);;
		break;
	case 3:
		randOne = FMath::RandHelper(modsMythic.Num());
		modOne = NewObject<UModBase>((UObject*)this, modsMythic[randOne]);;
		break;
	}

	int randTwo;

	sum_of_weight = 0;
	for (int i = 0; i < 4; i++) {
		sum_of_weight += curWeights[i];
	}
	rnd = FMath::RandRange(0, sum_of_weight);
	for (int i = 0; i < 4; i++) {
		if (rnd < curWeights[i])
		{
			rarity = i;
			break;
		}
		rnd -= curWeights[i];
	}

	bool mythicOut = true;
	UModBase* modTwo = nullptr;
	do
	{
		if (modTwo != NULL)
		{
			modTwo->ConditionalBeginDestroy();
		}

		switch (rarity)
		{
		case 0:
			randTwo = FMath::RandHelper(modsCommon.Num());
			modTwo = NewObject<UModBase>((UObject*)this, modsCommon[randTwo]);;
			break;
		case 1:
			randTwo = FMath::RandHelper(modsUncommon.Num());
			modTwo = NewObject<UModBase>((UObject*)this, modsUncommon[randTwo]);;
			break;
		case 2:
			randTwo = FMath::RandHelper(modsRare.Num());
			modTwo = NewObject<UModBase>((UObject*)this, modsRare[randTwo]);;
			break;
		case 3:
			randTwo = FMath::RandHelper(modsMythic.Num());
			modTwo = NewObject<UModBase>((UObject*)this, modsMythic[randTwo]);;
			mythicOut = false;
			break;
		}

	} while (modTwo->name == modOne->name && mythicOut);

	return TArray<UModBase*>{modOne, modTwo};
}


void AGun::LevelUp(UModBase* newModType)
{
	if (level == 0) {
		OnFirstUpgrade();
	}

	level++;

	AddMod(newModType);
	//AddMod(newModType);

	expToNextLevel = FMath::Square(expToNextLevel / 2) + (expToNextLevel / 2);
	if (GetLevelPercentage() != 1)
	{
		readyToLevelUp = false;
	}

	DisableUpgradeUI();

}


void AGun::UpdateCoreStats()
{
	int rofModStacks = 0;
	int damageModStacks = 0;
	int maxHealthStacks = 0;
	int curHealthStacks = 0;

	for (int i = 0; i < mods.Num(); i++)
	{
		for (ModAdditionalAtrributes atrib : mods[i]->atribs)
		{
			switch (atrib)
			{
			case ModAdditionalAtrributes::ATRIB_RATE_OF_FIRE:
				rofModStacks += mods[i]->stacks;
				break;
			case ModAdditionalAtrributes::ATRIB_DAMAGE_UP:
				damageModStacks += mods[i]->stacks;
				break;
			case ModAdditionalAtrributes::ATRIB_MAX_HEALTH_INCREASE:
				maxHealthStacks += mods[i]->stacks;
				break;
			case ModAdditionalAtrributes::ATRIB_CUR_HEALTH_INCREASE:
				curHealthStacks += mods[i]->stacks;
				break;
			default:
				break;
			}

		}

		
	}


	rpm = defaultRPM;
	for (int j = 0; j < rofModStacks; j++)
	{
		rpm *= rpmModifierRate;
	}

	Damage = defaultDamage;
	for (int j = 0; j < damageModStacks; j++)
	{
		Damage += damageModifier;
	}

	bulletSpeed = defaultBulletSpeed;


	UE_LOG(LogTemp, Warning, TEXT("Ammo Count: %d"), ammoCount);
	UE_LOG(LogTemp, Warning, TEXT("RPM: %d"), rpm);
	UE_LOG(LogTemp, Warning, TEXT("Reload Time: %f"), reloadTime);

}


FVector AGun::RaycastFromCamera()
{
	FVector cameraForward = camera->GetForwardVector();
	FVector cameraLoc = camera->GetComponentLocation();

	


	UWorld* World = GetWorld();
	FHitResult result;
	FVector start = cameraLoc + cameraForward * minRaycastDistance;
	FCollisionQueryParams CollisionParameters;
	FVector end = cameraLoc + cameraForward * maxRaycastDistance;

	World->LineTraceSingleByChannel(result, start, end, ECollisionChannel::ECC_Visibility);

	if (result.Actor != NULL)
	{
		return result.ImpactPoint;
	}
	else
	{
		return cameraLoc + cameraForward * maxRaycastDistance;
	}


}
