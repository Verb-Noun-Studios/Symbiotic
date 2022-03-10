// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaconActor.h"

#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

// Sets default values
ABeaconActor::ABeaconActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABeaconActor::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ABeaconActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	
}



void ABeaconActor::OnActivate()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling beacon base class activation"));
}

void ABeaconActor::OnDeactivate()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling beacon base class deactivation"));
}
