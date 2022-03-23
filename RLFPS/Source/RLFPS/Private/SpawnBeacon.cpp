// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBeacon.h"
#include "NavigationSystem.h"

void ASpawnBeacon::OnBeaconActivate_Implementation() {

	ABeaconActor::OnBeaconActivate_Implementation();
	
	UWorld* world = GetWorld();

	UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(world);

	FVector center = GetActorLocation();



	for (int i = 0; i < EnemySpawnCount; i++) {
		FNavLocation out_result;


		bool found = navSys->GetRandomPointInNavigableRadius(center, SpawnRadius, out_result);
		FString str = out_result.Location.ToString();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);

		FSpawnBeaconTrail SpawnTrail;
		SpawnTrail.delay = FMath::FRand();
		SpawnTrail.end = out_result.Location;
		SpawnTrail.t = 0;
		SpawnTrail.trail = GetWorld()->SpawnActor<AActor>(Trail.Get(), center, FRotator::ZeroRotator);
		SpawnTrail.speed = FVector::Dist(center, SpawnTrail.end);

		SpawnTrails.Add(SpawnTrail);
	}

	
}



void ASpawnBeacon::Tick(float dt) {
	Super::Tick(dt);
	if (IsBeaconEventActive()) {

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		if (SpawnTrails.Num() > 0) {
			FVector start = GetActorLocation();
			int activeCount = 0;
			for (FSpawnBeaconTrail& trail : SpawnTrails) {
				if (trail.t > 1.0f) continue;
				activeCount++;
				trail.delay -= dt;
				if (trail.delay > 0) continue;

				trail.t += dt / trail.speed * 150.0f;
				FVector pos = FMath::Lerp(start, trail.end, trail.t);
				pos.Z += FMath::Sin(trail.t * PI) * 400;


				trail.trail->SetActorLocation(pos);
				if (trail.t > 1.0f) {
					AGruntCharacter* enemy = GetWorld()->SpawnActor<AGruntCharacter>(EnemiesToSpawn.Get(), trail.end, FRotator::ZeroRotator, SpawnParams);
					if (enemy) EnemiesToKill.Push(enemy);
					trail.trail->Destroy();
				}

			}
			if (activeCount == 0) SpawnTrails.Empty();
		}
			
		if (SpawnTrails.Num() == 0 && AreAllEnemiesDead()) {
			BeaconEventComplete();
		}

		
	}
}


bool ASpawnBeacon::AreAllEnemiesDead() {
	
	for (TWeakObjectPtr<AGruntCharacter>& e : EnemiesToKill) {
		if (e.IsValid()) return false;
	}
	return true;
}
