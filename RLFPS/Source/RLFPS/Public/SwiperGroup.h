// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GruntCharacter.h"
#include "SwiperGroup.generated.h"


UCLASS()
class RLFPS_API ASwiperGroup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwiperGroup();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	
private:
	FVector location;
	float groupRadius;

	
};
