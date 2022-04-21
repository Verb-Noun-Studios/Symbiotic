// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "../FragPlayer.h"
#include "Engine.h"
#include "ConvexVolume.h"
#include "Kismet/KismetMathLibrary.h"
//#include "NavigationSystem.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	enemiesSpawned = 0;
	Player = (AFragPlayer*)UGameplayStatics::GetActorOfClass(GetWorld(), AFragPlayer::StaticClass());
	//SpawnInitialEnemies();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	elapsedTime += DeltaTime;

	if (activated)
	{

		if (boostTime > 0)
		{
			boostTime -= DeltaTime;

			if (elapsedTime >= 60.0 / (SpawnRate * boostMultiplier))
			{
				TrySpawn();

				enemiesSpawned++;
				elapsedTime = 0;
			}
		}
		else
		{
			if (elapsedTime >= 60.0 / SpawnRate)
			{
				TrySpawn();
				enemiesSpawned++;
				elapsedTime = 0;
	
			}	
		}
	}

	

}

void AEnemySpawner::Boost(float BeaconTime, float BeaconMultiplier)
{
	boostTime = BeaconTime;
	boostMultiplier = BeaconMultiplier;
}

void AEnemySpawner::SpawnInitialEnemies()
{
	TrySpawnMultiple(InitialEnemies);
}

bool AEnemySpawner::SpawnEnemy() {
	
	FVector point;
	bool success = GetRandomNavPoint(point);


	// is point infront of player
	FVector forward = Player->FirstPersonCameraComponent->GetForwardVector();
	FVector pointLookDir = (point - Player->GetActorLocation()).GetSafeNormal();
	

	TSubclassOf<AActor> type = GetRandomType();
	UCapsuleComponent* component = (UCapsuleComponent*)type.GetDefaultObject()->GetComponentByClass(UCapsuleComponent::StaticClass());

	if (component == nullptr) return false;
	FVector pos = component->GetRelativeLocation() + point;
	float halfheight = component->GetScaledCapsuleHalfHeight();
	float radius = component->GetScaledCapsuleRadius();

	FConvexVolume camVolume;
	FMinimalViewInfo viewInfo;
	Player->FirstPersonCameraComponent->GetCameraView(0, viewInfo);
		
	FMatrix viewProjection = FLookFromMatrix(viewInfo.Location, viewInfo.Rotation.RotateVector(FVector::ForwardVector), FVector::UpVector);
	viewProjection *= viewInfo.CalculateProjectionMatrix();
	
	GetViewFrustumBounds(camVolume, viewProjection, false);
	

	if (camVolume.IntersectBox(component->Bounds.Origin + point, component->Bounds.BoxExtent)) {
		//return false;
		//const FName TraceTag("MyTraceTag");

		//GetWorld()->DebugDrawTraceTag = TraceTag;

		FCollisionQueryParams traceParams;
		traceParams.AddIgnoredActor(Player);
		//traceParams.TraceTag = TraceTag;

		TArray<TEnumAsByte<EObjectTypeQuery>> typeQuery;
		TArray<AActor*> ignoreActors;
		TArray<AActor*> outActors;

		//bool hit = UKismetSystemLibrary::CapsuleOverlapActors(GetWorld(), point + 110, 30, 100, typeQuery, NULL, ignoreActors, outActors);

		//if (hit) return false;

		FHitResult result;
		bool hit0 = GetWorld()->LineTraceSingleByChannel(result, point + FVector(0, 0,   0), viewInfo.Location, ECollisionChannel::ECC_WorldStatic, traceParams);
		bool hit1 = GetWorld()->LineTraceSingleByChannel(result, point + FVector(0, 0, 50), viewInfo.Location, ECollisionChannel::ECC_WorldStatic, traceParams);
		bool hit2 = GetWorld()->LineTraceSingleByChannel(result, point + FVector(0, 0, 100), viewInfo.Location, ECollisionChannel::ECC_WorldStatic, traceParams);

		// if any of the hits dont hit anything, don't spawn
		if (!(hit0 && hit1 && hit2)) return false;
		
		
		/*
		// DEBUG VISUALIZATION STUFF
		DrawDebugLine(GetWorld(), point + FVector(0, 0, 0),   viewInfo.Location, FColor::Cyan,  true);
		DrawDebugLine(GetWorld(), point + FVector(0, 0, 100), viewInfo.Location, FColor::Cyan, true);
		DrawDebugLine(GetWorld(), point + FVector(0, 0, 200), viewInfo.Location, FColor::Cyan,  true);
		DrawDebugLine(GetWorld(), point + FVector(0, 0, 300), viewInfo.Location, FColor::Cyan,  true);

		DrawDebugSphere(GetWorld(), point, 10, 16, FColor::Orange, true);
		*/
	}
		



	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	AActor* actor = GetWorld()->SpawnActor(type.Get(), &point, nullptr, spawnParams);

	if (actor == nullptr) {
		
		/*
		// DEBUG VISUALIZATION STUFF
		DrawDebugCapsule(GetWorld(), pos, halfheight, radius, FQuat::Identity, FColor::Orange, true, -1, 100);
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn, displaying capsule %f, %f"), halfheight, radius);
		*/
		return false;
	}

	// tell the blueprint that we spawned an enemy
	OnSpawnEnemy(actor);

	return true;
}

bool AEnemySpawner::TrySpawn() {
	int attempts = 0;
	const int max_attempts = 20;

	while (attempts < max_attempts) {
		bool spawned;
		spawned = SpawnEnemy();
		if (spawned) return true;

		attempts++;
	}

	UE_LOG(LogTemp, Warning, TEXT("Failed to spawn enemy after %d attempts"), attempts);
	return false;
}

TSubclassOf<AActor> AEnemySpawner::GetRandomType() {
	float r = FMath::FRand();

	for (const FEnemySpawnChoice& choice : SpawnChoices) {
		r -= choice.chance;
		if (r <= 0)
			return choice.type;
	}

	return SpawnChoices[SpawnChoices.Num() - 1].type;
}

bool AEnemySpawner::TrySpawnMultiple(int count) {

	for (int success_count = 0; success_count < count; success_count++) {
		bool success = TrySpawn();
		if (!success)
			return false;
	}

	return true;
};

bool AEnemySpawner::GetRandomNavPoint(FVector& out_point) {
	if (PolyCache.Num() == 0) {
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
		ARecastNavMesh* NavData = (ARecastNavMesh*)NavSys->GetDefaultNavDataInstance();

		FVector pos = GetActorLocation();
		FBox box(pos, pos);
		box = box.ExpandBy(3000);
		NavData->GetPolysInBox(box, PolyCache);
	}

	// TODO: (thornton) this might cause alot of lag if there is no mesh yet
	if (PolyCache.Num() == 0) return false;

	const int32 RandomIndex = FMath::RandHelper(PolyCache.Num());
	const FNavPoly& Poly = PolyCache[RandomIndex];

	//return FNavLocation(Poly.Center, Poly.Ref);
	out_point = Poly.Center;
	return true;
}