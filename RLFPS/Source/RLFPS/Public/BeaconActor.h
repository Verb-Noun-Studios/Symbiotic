// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeaconActor.generated.h"

class ASpawningActor;

UCLASS()
class RLFPS_API ABeaconActor : public AActor
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<ASpawningActor*> spawnPoints;
public:	
	// Sets default values for this actor's properties
	ABeaconActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float multiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float time;

	void GetSpawnPoints();
	UFUNCTION(BlueprintCallable)
	void Activate();




};
