// Fill out your copyright notice in the Description page of Project Settings.

#include "GruntHelperSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "GruntCharacter.h"



void UGruntHelperSubsystem::Tick(float deltaTime) {
	/*
	TArray<AActor*> ActorRefs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGruntCharacter::StaticClass(), ActorRefs);

	GruntRefs.Empty(ActorRefs.Num());
	for (AActor* ptr : ActorRefs) {
		GruntRefs.Push((AGruntCharacter*)ptr);
	}

	GruntPositions.Empty(ActorRefs.Num());
	for (AActor* ptr : ActorRefs) {
		GruntPositions.Push(ptr->GetActorLocation());
	}
	*/
}


TArray<AGruntCharacter*> UGruntHelperSubsystem::GetGruntsInRadius(FVector pos, float radius) {
	TArray<AGruntCharacter*> grunts;
	float radiusSqr = radius * radius;

	for (int i = 0; i < GruntRefs.Num(); i++) {
		if (FVector::DistSquared(GruntPositions[i], pos) <= radiusSqr)
			grunts.Push(GruntRefs[i]);
	}

	return grunts;
}


AGruntCharacter* UGruntHelperSubsystem::GetGruntAtIndex(int index) {
	return GruntRefs[index];
}


FVector UGruntHelperSubsystem::GetGruntPosAtIndex(int index) {
	return GruntPositions[index];
}

ETickableTickType UGruntHelperSubsystem::GetTickableTickType() const
{
	return ETickableTickType::Always;
}

TStatId UGruntHelperSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UGruntHelperSubsystem, STATGROUP_Tickables);
}