// Fill out your copyright notice in the Description page of Project Settings.


#include "GunModBase.h"

UGunModBase::UGunModBase()
{

}

UGunModBase::~UGunModBase()
{

}

void UGunModBase::OnApply()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Base Gun Mod On Apply"));
}