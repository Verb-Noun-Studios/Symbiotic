// Fill out your copyright notice in the Description page of Project Settings.


#include "IncreasedMagMod.h"

UIncreasedMagMod::UIncreasedMagMod()
{

}

UIncreasedMagMod::~UIncreasedMagMod()
{

}

void UIncreasedMagMod::OnApply(float& reloadTime, int& ammoCount, float& bulletSpeed, int& rpm)
{
	ammoCount *= 2;
}
