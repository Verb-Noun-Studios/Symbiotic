// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GruntCharacter.h"
#include "Acid.generated.h"

UCLASS()
class RLFPS_API AAcid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAcid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AGruntCharacter*> enemies;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float damage = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float duration = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float interval = 0.3;
};
