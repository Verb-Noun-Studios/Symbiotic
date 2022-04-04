// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ModBase.h"
#include "SaveControllerSubsystem.generated.h"


/**
 * Subsystem to load and manage mods
 * might be used to select which mods are going to be options for the player
 * 
 */

class AGun;
class AFragPlayer;

UCLASS()
class RLFPS_API USaveControllerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:
    // Begin USubsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    // End USubsystem

    //TArray<FSavedModInfo>& GetSavedMods() { return savedMods;  }

   
    void LoadPlayerData(AFragPlayer* player);
    void SavePlayerData(AFragPlayer* player);

    void LoadGunData(AGun* gun);
    void SaveGunData(AGun* gun);


    /* SAVE DATA */

    /* GUN SAVE DATA*/
    UPROPERTY()
    TArray<TSubclassOf<UModBase>> subclasses;

    UPROPERTY()
    TArray <int> stacks;

   
    // mark the data as invalid, will only be valid once it has been loaded again
    UFUNCTION(BlueprintCallable)
    void InvalidateData() {
        bHasValidData = false;
        stacks.Empty();
        subclasses.Empty();

        KilledEnemies = 0;
    }

private:

    float PlayerHP;

    int KilledEnemies;

    bool bHasValidData = false;
};


