// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAmmoMod.h"

UTestAmmoMod::UTestAmmoMod()
{

}

UTestAmmoMod::~UTestAmmoMod()
{

}

void UTestAmmoMod::OnApply()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Test On Apply"));
}

void UTestAmmoMod::OnHit(AActor* actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Test On Hit"));
}