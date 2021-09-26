// Fill out your copyright notice in the Description page of Project Settings.


#include "ModActor.h"

// Sets default values
AModActor::AModActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AModActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AModActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

