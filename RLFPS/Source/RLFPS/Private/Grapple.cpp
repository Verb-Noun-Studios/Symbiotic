// Fill out your copyright notice in the Description page of Project Settings.


#include "Grapple.h"

// Sets default values
AGrapple::AGrapple()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrapple::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrapple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AGrapple::OnStart_Implementation(AActor* gun, AActor* hitActor, FVector hitPointOffset)
{

}
