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
	
private:
	bool EventStarted = false;
	bool EventComplete = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;;
	UPROPERTY(BlueprintReadOnly)
	bool eventComplete = false;
	

	// MUST BE CALLED TO END THE BEACON
	UFUNCTION(BlueprintCallable)
		void BeaconEventComplete();

	UFUNCTION(BlueprintNativeEvent)
		bool CanBeaconActivate(); 

	virtual bool CanBeaconActivate_Implementation() { return !IsBeaconEventStarted(); }

public:	
	// Sets default values for this actor's properties
	ABeaconActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// start the beacon event, starts the event (if CanActivate() returns true), called by Use()
	UFUNCTION(BlueprintCallable)
		void BeaconEventStart();


	UFUNCTION(BlueprintNativeEvent)
		void OnBeaconActivate();

	UFUNCTION(BlueprintNativeEvent)
		void OnBeaconDeactivate();

	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayActivationSound();

	UFUNCTION(BlueprintCallable)
	bool IsBeaconEventStarted() const;

	UFUNCTION(BlueprintCallable)
	bool IsBeaconEventActive() const;


	UFUNCTION(BlueprintCallable)
	bool IsBeaconEventComplete() const;


	virtual void Use_Implementation() override { if (CanBeaconActivate()) { BeaconEventStart(); } }

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//void Use();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UModBase> newMod;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* MeshTop;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* MeshBottom;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		USceneComponent* SceneRootComponent;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* BurntOutMaterial;

	// DOESNT DO ANYTHING RIGHT NOW
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundBase* ActivationSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RotateSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BobSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BobMagnitude;

private:
	float RotateTime = 0;
};
