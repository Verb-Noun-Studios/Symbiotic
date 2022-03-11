// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaconActor.h"

#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

// Sets default values
ABeaconActor::ABeaconActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	//RootComponent->GetComponentTransform().Set

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = SceneRootComponent;

	MeshTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopHalf"));
	MeshBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomHalf"));

	MeshTop->SetupAttachment(RootComponent);
	MeshBottom->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABeaconActor::BeginPlay()
{
	Super::BeginPlay();

	RotateTime += FMath::FRand();
}

// Called every frame
void ABeaconActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!IsBeaconEventComplete()) {
		RotateTime += DeltaTime;

		float rotate = RotateTime * RotateSpeed;
		float bob = FMath::Sin(RotateTime * BobSpeed) * BobMagnitude;
		MeshTop->SetRelativeLocationAndRotation(FVector::UpVector * bob, FQuat(FVector::UpVector, rotate));
	}

}



void ABeaconActor::OnActivate()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling beacon base class activation"));
}

void ABeaconActor::OnDeactivate()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling beacon base class deactivation"));
}



// MUST BE CALLED WHEN A BEACON EVENT IS STARTED
void ABeaconActor::BeaconEventStart() {
	EventStarted = true;
	OnActivate();
}

// MUST BE CALLED ONCE THE BEACON EVENT HAS FINISHED
void ABeaconActor::BeaconEventComplete() {
	if (EventStarted == false) UE_LOG(LogActor, Warning, TEXT("BeaconEventComplete called but EventStarted was false"));
	EventComplete = true;
	OnDeactivate();

	float RandX = FMath::FRandRange(0.3, 0.7);
	float RandZ = FMath::FRand() * PI * 2; // full rotation
	FQuat rot = FQuat(FVector::UpVector, RandZ) * FQuat(FVector::RightVector, RandX);
	MeshTop->SetRelativeLocationAndRotation(FVector::UpVector * -10, rot);

	MeshTop->SetMaterial(1, BurntOutMaterial);
	MeshBottom->SetMaterial(1, BurntOutMaterial);
}

bool ABeaconActor::IsBeaconEventStarted() const {
	return EventStarted;
}


bool ABeaconActor::IsBeaconEventActive() const {
	return EventStarted && !EventComplete;
}


bool ABeaconActor::IsBeaconEventComplete() const {
	return EventComplete;
}