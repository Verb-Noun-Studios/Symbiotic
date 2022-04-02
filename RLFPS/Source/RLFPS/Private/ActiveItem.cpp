// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveItem.h"

UActiveItem::UActiveItem()
{
}

UActiveItem::~UActiveItem()
{

}



void UActiveItem::OnActiveAbility_Implementation(AActor* gun)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling base active item."));
}



void UActiveItem::BeginRecharge() {
	if (passiveRechargeTime > 0) {
		GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UActiveItem::FinishRecharge, passiveRechargeTime);
	}
}

void UActiveItem::FinishRecharge() {
	currentKillCount = requiredKillCount;
}