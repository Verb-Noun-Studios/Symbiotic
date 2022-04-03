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

	KilledEnemies = gun->KilledEnemies;
}


void USaveControllerSubsystem::LoadGunData(AGun* gun) {
	if (!bHasValidData) return;
	

	TArray<UModBase*>& mods = gun->mods;

	mods.Empty();
	mods.Reserve(subclasses.Num());
	for (int i = 0; i < subclasses.Num(); i++) {
		UModBase * mod = NewObject<UModBase>(gun, subclasses[i]);
		int stack_count = stacks[i];
		// I hate this :(
		mods.Add(mod);
		for (int j = 0; j < stack_count; j++) {
			mod->stacks = j;
			mod->OnApply(gun->player);
		}
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