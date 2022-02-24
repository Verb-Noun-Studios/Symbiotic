// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.h"
#include "Doorway.generated.h"

UCLASS()
class RLFPS_API ADoorway : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorway();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//   0 = closed,  1 = open
	UPROPERTY(BlueprintReadWrite)
	float opennessValue = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float speed = 0.02;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool shouldbeOpen;

	//false = exit, true = entrance
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Entrance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SlideOffset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AEnemySpawner* spawner;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InterpolateDoor();

};
