// Fill out your copyright notice in the Description page of Project Settings.


#include "ModControllerSubsystem.h"
#include "ModBase.h"

void UModControllerSubsystem::Initialize(FSubsystemCollectionBase& Collection) {

}


void UModControllerSubsystem::Deinitialize() {

}


void UModControllerSubsystem::SaveMods(const TArray<UModBase*>& mods) {
	savedMods.Empty();
	savedMods.Reserve(mods.Num());
	for (UModBase* mod : mods) {
		SavedModInfo info;
		info.subclass = mod->GetClass();
		info.stacks = mod->stacks;

		savedMods.Add(info);
	}
}



void UModControllerSubsystem::LoadMods(TArray<UModBase*>& mods, UObject* outer) {
	mods.Empty();
	mods.Reserve(savedMods.Num());
	for (SavedModInfo info : savedMods) {
		UModBase* mod = NewObject<UModBase>(outer, info.subclass);
		mod->stacks = info.stacks;
		mods.Add(mod);
	}
	savedMods.Empty();
}

