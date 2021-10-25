// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "ModBase.h"
#include "BeaconActor.generated.h"

class ASpawningActor;

UCLASS()
class RLFPS_API ABeaconActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<ASpawningActor*> spawnPoints;
	float timeRemaining;
	UPROPERTY(BlueprintReadOnly)
	bool eventComplete = false;
	
public:	
	// Sets default values for this actor's properties
	ABeaconActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool activated = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float multiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UModBase> newMod;
	
	void GetSpawnPoints();
	UFUNCTION(BlueprintCallable)
	void Activate();
	UFUNCTION(BlueprintNativeEvent)
	void RecieveOnActivate();

	UFUNCTION(BlueprintCallable)
	void Use();

};
