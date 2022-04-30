// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveControllerSubsystem.h"
#include "../FragPlayer.h"
#include "HealthComponent.h"
#include "Gun.h"
#include "ModBase.h"

void USaveControllerSubsystem::Initialize(FSubsystemCollectionBase& Collection) {

}


void USaveControllerSubsystem::Deinitialize() {

}


void USaveControllerSubsystem::SaveGunData(AGun* gun) {
	if (!bHasValidData) return;
	const TArray<UModBase*>& mods = gun->mods;
	
	subclasses.Empty();
	stacks.Empty();
	subclasses.Reserve(mods.Num());
	stacks.Reserve(mods.Num());
	
	for (UModBase* mod : mods) {
		subclasses.Add(mod->GetClass());
		stacks.Add(mod->stacks);
	}

	if (gun->activeItem) {
		subclasses.Add(gun->activeItem->GetClass());
		stacks.Add(1);
	}

	KilledEnemies = gun->KilledEnemies;
}


void USaveControllerSubsystem::LoadGunData(AGun* gun) {
	if (!bHasValidData) return;
	

	for (int i = 0; i < subclasses.Num(); i++) {
		for (int j = 0; j < stacks[i]; j++)
			gun->AddMod(subclasses[i]);
	}
	stacks.Empty();
	subclasses.Empty();

	gun->KilledEnemies = KilledEnemies;

	
}




void USaveControllerSubsystem::LoadPlayerData(AFragPlayer* player) {
	if (!bHasValidData) {
		bHasValidData = true;
		return;
	}
	player->HealthComponent->currentHealth = PlayerHP;
}

void USaveControllerSubsystem::SavePlayerData(AFragPlayer* player) {
	if (!bHasValidData) return;

	PlayerHP = player->HealthComponent->currentHealth;
}