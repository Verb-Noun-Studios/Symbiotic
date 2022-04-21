// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaconActor.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"
#include "Gun.h"
#include "ActiveItem.h"

// Sets default values
ABeaconActor::ABeaconActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	//RootComponent->GetComponentTransform().Set

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SceneRootComponent->SetMobility(EComponentMobility::Static);
	RootComponent = SceneRootComponent;

	
	MeshBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomHalf"));
	MeshTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopHalf"));



	MeshBottom->SetupAttachment(RootComponent);
	MeshTop->SetupAttachment(RootComponent);

	UClass* Class = GetClass();
	ABeaconActor* Defaults = (ABeaconActor*)Class->GetDefaultObject();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Defaults->GetName());
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
		MeshTop->SetRelativeLocationAndRotation(FVector::UpVector * (bob + 50), FQuat(FVector::UpVector, rotate));
	}

}



void ABeaconActor::OnBeaconActivate_Implementation()
{
	
}

void ABeaconActor::OnBeaconDeactivate_Implementation()
{
}



// MUST BE CALLED WHEN A BEACON EVENT IS STARTED
void ABeaconActor::BeaconEventStart() {
	EventStarted = true;
	OnBeaconActivate();
}

// MUST BE CALLED ONCE THE BEACON EVENT HAS FINISHED
void ABeaconActor::BeaconEventComplete() {
	if (EventStarted == false) UE_LOG(LogActor, Warning, TEXT("BeaconEventComplete called but EventStarted was false"));
	EventComplete = true;
	OnBeaconDeactivate();

	float RandX = FMath::FRandRange(0.3, 0.7);
	float RandZ = FMath::FRand() * PI * 2; // full rotation
	FQuat rot = FQuat(FVector::UpVector, RandZ) * FQuat(FVector::RightVector, RandX);
	MeshTop->SetRelativeLocationAndRotation(FVector::UpVector * 40, rot);

	MeshTop->SetMaterial(1, BurntOutMaterial);
	MeshBottom->SetMaterial(1, BurntOutMaterial);

	AGun* gun = (AGun*)UGameplayStatics::GetActorOfClass(GetWorld(), AGun::StaticClass() );

	
	
	if (!UKismetMathLibrary::ClassIsChildOf(newMod,UActiveItem::StaticClass()))
	{
		UE_LOG(LogActor, Warning, TEXT("Failed to cast to active item"));
		gun->AddMod(newMod);

	}
	else
	{
		UActiveItem* activeItem = NewObject<UActiveItem>((UObject*)this, newMod);;
		gun->ReplaceActiveItem(activeItem);
		UE_LOG(LogActor, Warning, TEXT("Adding Active Item"));
	}
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