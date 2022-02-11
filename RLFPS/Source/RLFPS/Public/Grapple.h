// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Grapple.generated.h"

UCLASS()
class RLFPS_API AGrapple : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrapple();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector startLoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector endLoc;

	UFUNCTION(BlueprintNativeEvent)
	void OnStart(AActor* gun);//, AActor* hitActor, FVector hitPointOffset


};
