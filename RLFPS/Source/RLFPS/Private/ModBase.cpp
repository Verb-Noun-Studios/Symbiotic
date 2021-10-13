// Fill out your copyright notice in the Description page of Project Settings.


#include "ModBase.h"
#include "Bullet.h"

UModBase::UModBase()
{
}

UModBase::~UModBase()
{
}


void UModBase::OnApply()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Base Mod On Apply"));
}

void UModBase::OnFire(AGun* gun)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Base Mod On Fire"));
	
}

void UModBase::OnHit(AActor* actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Test On Hit"));
}