// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModBase.generated.h"

UENUM()
enum class ModType : uint8
{
	MOD_GUN		UMETA(DisplayName = "Gun Mod"),
	MOD_AMMO		UMETA(DisplayName = "Ammo Mod"),
};






/**
 * 
 */
UCLASS()
class RLFPS_API UModBase : public UObject
{

	GENERATED_BODY()
public:
	UModBase();
	~UModBase();

	ModType type;
	int stacks = 1;


	


};
