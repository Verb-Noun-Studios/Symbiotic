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
	

	// MUST BE CALLED WHEN A BEACON EVENT IS STARTED
	UFUNCTION(BlueprintCallable)
		void BeaconEventStart();

	// MUST BE CALLED ONCE THE BEACON EVENT HAS FINISHED
	UFUNCTION(BlueprintCallable)
		void BeaconEventComplete();


public:	
	// Sets default values for this actor's properties
	ABeaconActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UModBase> newMod;
	

	UFUNCTION(BlueprintCallable)
	void OnActivate();
	UFUNCTION(BlueprintCallable)
	void OnDeactivate();

	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayActivationSound();

	UFUNCTION(BlueprintCallable)
	bool IsBeaconEventStarted() const;

	UFUNCTION(BlueprintCallable)
	bool IsBeaconEventActive() const;


	UFUNCTION(BlueprintCallable)
	bool IsBeaconEventComplete() const;



	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//void Use();
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* MeshTop;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* MeshBottom;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		USceneComponent* SceneRootComponent;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* BurntOutMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RotateSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BobSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BobMagnitude;

private:
	float RotateTime = 0;
};
