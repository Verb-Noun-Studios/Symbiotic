// Fill out your copyright notice in the Description page of Project Settings.


#include "ModControllerSubsystem.h"
#include "ModBase.h"

void UModControllerSubsystem::Initialize(FSubsystemCollectionBase& Collection) {

}


void UModControllerSubsystem::Deinitialize() {

}


void UModControllerSubsystem::SaveMods(const TArray<UModBase*>& mods) {
	
	subclasses.Empty();
	stacks.Empty();
	subclasses.Reserve(mods.Num());
	stacks.Reserve(mods.Num());
	
	for (UModBase* mod : mods) {
		subclasses.Add(mod->GetClass());
		stacks.Add(mod->stacks);
	}
}



void UModControllerSubsystem::LoadMods(TArray<UModBase*>& mods, UObject * outer) {
	mods.Empty();
	mods.Reserve(subclasses.Num());
	for (int i = 0; i < subclasses.Num(); i++) {
		UModBase * mod = NewObject<UModBase>(outer, subclasses[i]);
	
		mod->stacks = stacks[i];
		mods.Add(mod);
	}
	stacks.Empty();
	subclasses.Empty();
}

