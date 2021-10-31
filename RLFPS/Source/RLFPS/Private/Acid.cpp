// Fill out your copyright notice in the Description page of Project Settings.


#include "Acid.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAcid::AAcid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAcid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAcid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

