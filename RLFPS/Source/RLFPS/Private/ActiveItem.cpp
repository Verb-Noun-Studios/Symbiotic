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

