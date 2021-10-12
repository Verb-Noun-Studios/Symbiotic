// Fill out your copyright notice in the Description page of Project Settings.


#include "IncreasedMagMod.h"

UIncreasedMagMod::UIncreasedMagMod()
{

}

UIncreasedMagMod::~UIncreasedMagMod()
{
	atribs.Add(ModAdditionalAtrributes::ATRIB_INCREASED_MAG);
}




void UIncreasedMagMod::OnApply()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Mag Mod On Apply"));
	//ammoCount *= 2;
}

void UIncreasedMagMod::OnHit(AActor* actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Test On Hit"));
}