// Fill out your copyright notice in the Description page of Project Settings.

//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Subsystems/WorldSubsystem.h"
//#include "Tickable.h"
//#include "GruntHelperSubsystem.generated.h"
//
//
//class AGruntCharacter;
///**
// * A helper to make operations on large numbers of grunts faster/easier
// */
//UCLASS()
//class RLFPS_API UGruntHelperSubsystem : public UWorldSubsystem, public FTickableGameObject
//{
//    GENERATED_BODY()
//
//
//    TArray<AGruntCharacter*> GruntRefs;
//    TArray<FVector> GruntPositions;
//public:
// 
//
//
//    TArray<AGruntCharacter*> GetGruntsInRadius(FVector pos, float radius);
//    AGruntCharacter* GetGruntAtIndex(int index);
//    FVector GetGruntPosAtIndex(int index);
//
//
//    virtual void Tick(float DeltaTime) override;
//    virtual ETickableTickType GetTickableTickType() const override;
//    virtual TStatId GetStatId() const override;
//};
//
