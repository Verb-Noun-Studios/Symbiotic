// Fill out your copyright notice in the Description page of Project Settings.


#include "Doorway.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADoorway::ADoorway()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorway::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorway::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InterpolateDoor();

}

void ADoorway::InterpolateDoor()
{
	if (shouldbeOpen)
	{
		opennessValue += speed;
	}
	else
	{
		opennessValue -= speed;
	}

	opennessValue = FMath::Clamp(opennessValue, 0.0f, 1.0f);
}