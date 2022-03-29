// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include "Sound/SoundWave.h"
#include "ModBase.generated.h"

UENUM()
enum class ModType : uint8
{
	MOD_GUN		UMETA(DisplayName = "Gun Mod"),
	MOD_AMMO	UMETA(DisplayName = "Ammo Mod"),
	MOD_PLAYER	UMETA(DisplayName = "Player Mod"),
};


UENUM()
enum class ModSubType : uint8
{
	MOD_GUN_ROF				UMETA(DisplayName = "Gun Mod: ROF"),
	MOD_GUN_AMMO			UMETA(DisplayName = "Gun Mod: Ammo Capacity"),
	MOD_AMMO_EXPLODING		UMETA(DisplayName = "Ammo Mod: Exploading"),
	MOD_AMMO_RICOCHET		UMETA(DisplayName = "Ammo Mod: Ricocheting"),
};


UENUM()
enum class ModAdditionalAtrributes : uint8
{
	
	ATRIB_INCREASED_MAG			UMETA(DisplayName = "Magazine Increase"),
	ATRIB_RATE_OF_FIRE			UMETA(DisplayName = "Rate of Fire"),
	ATRIB_REDUCED_RELOAD_TIME	UMETA(DisplayName = "Reduced Reload Time"),
	ATRIB_MAX_HEALTH_INCREASE	UMETA(DisplayName = "Increase Max Health"),
	ATRIB_CUR_HEALTH_INCREASE	UMETA(DisplayName = "Increase Current Health"),
};


class ABullet;
class AGun;
/**
 * 
 */
UCLASS(Blueprintable)
class RLFPS_API UModBase : public UObject
{

	GENERATED_BODY()
public:
	UModBase();
	~UModBase();


	/********** FUNCTIONS *************/
	UFUNCTION(BlueprintNativeEvent)
	void OnApply(AFragPlayer* player);

	UFUNCTION(BlueprintNativeEvent)
	void OnSpawn(ABullet* bullet);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnFire(AGun* gun);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnHit(AActor* hitActor, UWorld* world);

	UFUNCTION(BlueprintNativeEvent)
	void OnReload(AActor* player);


	
	UFUNCTION(BlueprintCallable)
	AActor* GetActorOfClass_Internal(TSubclassOf<AActor> actorClass);

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetActorsOfClass_Internal(TSubclassOf<AActor> actorClass);
	
	UFUNCTION(BlueprintCallable)
	UWorld* GetWorld_Internal();

	UFUNCTION(BlueprintCallable)
	UNiagaraComponent* SpawnSystemAtLocation_Internal( UNiagaraSystem* system, FVector location, FRotator rotation, FVector scale);

	UFUNCTION(BlueprintCallable)
	AActor* SpawnActorOfClass_Internal(AActor* owner, TSubclassOf<AActor> actorClass, FVector const& loc, FRotator const& rot);


	
	
	
	/********** VARIABLES *************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ModType type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString infoText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString effectText;

	UPROPERTY(BlueprintReadOnly)
	int stacks = 1;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int rarity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ModAdditionalAtrributes> atribs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* niagaraVFX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave* sound;


};
