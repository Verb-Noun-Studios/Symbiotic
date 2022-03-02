// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffect.h"
#include "Kismet/GameplayStatics.h"
#include "GruntCharacter.h"

UStatusEffect::UStatusEffect()
{
	timeRemaining = duration;
}

UStatusEffect::~UStatusEffect()
{

}

void UStatusEffect::OnTick_Implementation(AActor* actor, float deltaTime)
{
	timeRemaining -= deltaTime;
	timeSinceLastTick += deltaTime;
	//UE_LOG(LogTemp, Warning, TEXT("Time Remaining: %f"), timeRemaining);

	if (timeRemaining <= 0)
	{
		stacks--;
		if (stacks < 1)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Destroying"));
			dead = true;
		}
		timeRemaining = duration;
		owner->UpdateStatusEffects();
	
		
	}
}

AActor* UStatusEffect::GetActorOfClass_Internal(TSubclassOf<AActor> actorClass)
{
	UWorld* world = GetWorld();

	return UGameplayStatics::GetActorOfClass(world, actorClass);

}

TArray<AActor*> UStatusEffect::GetActorsOfClass_Internal(TSubclassOf<AActor> actorClass)
{
	UWorld* world = GetWorld();
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(world, actorClass, OutActors);
	return OutActors;

}


UWorld* UStatusEffect::GetWorld_Internal()
{
	return GetWorld();
}

