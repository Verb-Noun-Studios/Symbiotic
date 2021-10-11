// Fill out your copyright notice in the Description page of Project Settings.


#include "IncreasedMagMod.h"

UIncreasedMagMod::UIncreasedMagMod()
{

}

UIncreasedMagMod::~UIncreasedMagMod()
{

}



//float& reloadTime, int& ammoCount, float& bulletSpeed, int& rpm
void UIncreasedMagMod::OnApply()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Mag Mod On Apply"));
	//ammoCount *= 2;
}
