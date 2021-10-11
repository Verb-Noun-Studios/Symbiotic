// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoModBase.h"

UAmmoModBase::UAmmoModBase()
{

}
UAmmoModBase::~UAmmoModBase()
{

}

void UAmmoModBase::OnApply()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Base Ammo Mod On Apply"));
}

void UAmmoModBase::OnHit(AActor* actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Base Ammo Mod On Hit"));
}