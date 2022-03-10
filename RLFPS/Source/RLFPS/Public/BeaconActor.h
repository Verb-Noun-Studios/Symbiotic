// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "ActiveItem.h"
#include "EnemySpawner.h"
#include "BeaconActor.generated.h"



UCLASS()
class RLFPS_API ABeaconActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;;
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
	TSubclassOf<UModBase> newMod;
	

	UFUNCTION(BlueprintCallable)
	void OnActivate();
	UFUNCTION(BlueprintCallable)
	void OnDeactivate();

	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayActivationSound();

	//virtual void Use_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Use();
};
