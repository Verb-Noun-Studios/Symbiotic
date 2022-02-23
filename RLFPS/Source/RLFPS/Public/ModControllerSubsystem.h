// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ModBase.h"
#include "ModControllerSubsystem.generated.h"


/**
 * Subsystem to load and manage mods
 * might be used to select which mods are going to be options for the player
 * 
 */


UCLASS()
class RLFPS_API UModControllerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:
    // Begin USubsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    // End USubsystem

 
    // This is kind of sucks, might be better for this class to manage the active mods
    // in order to make it better I would have to change the lifecyle of the mods on the gun
    // which seems like something we should talk about first
    void SaveMods(const TArray<UModBase*>& mods);
    void LoadMods(TArray<UModBase*>& mods, UObject* outer);

    //TArray<FSavedModInfo>& GetSavedMods() { return savedMods;  }

    UPROPERTY()
    TArray< TSubclassOf<UModBase>> subclasses;

    UPROPERTY()
    TArray <int> stacks;
    //TArray<FSavedModInfo> savedMods;

   
};


