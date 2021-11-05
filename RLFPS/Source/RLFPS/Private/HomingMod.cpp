// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingMod.h"
#include "Bullet.h"
#include "Kismet/KismetMathLibrary.h"



UHomingMod::UHomingMod()
{

}


UHomingMod::~UHomingMod()
{

}


void UHomingMod::OnSpawn_Implementation(ABullet* bullet)
{
	bullet->ProjectileMovementComponent->bIsHomingProjectile = true;
	bullet->HomingStrength = bullet->initialHomingStrength + (bullet->HomingStackingStrength * stacks);
	bullet->ProjectileMovementComponent->HomingAccelerationMagnitude = bullet->HomingStrength;
	float range = bullet->initialHomingRange + (bullet->HomingRangeStackingStrength * stacks);
	UE_LOG(LogTemp, Warning, TEXT("Setting Homing Range: %f "), range);
	bullet->homingRange = range;

	TArray<AActor*> enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), bullet->targetClass, enemies);
	AActor* closestPlayer = nullptr;
	float distance = INT_MAX;

	//log all actors found for debugging
	for (AActor* actor : enemies)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Names: %s"), *actor->GetName());
	}

	for (AActor* actor : enemies)
	{
		
		FHitResult OutHit;

		FCollisionQueryParams CollisionParams;
		GetWorld()->LineTraceSingleByChannel(OutHit, bullet->GetActorLocation(), actor->GetActorLocation(), ECC_Visibility, CollisionParams);

		if (OutHit.Actor != actor)
		{

		}
		else
		{

			FVector dir = actor->GetActorLocation() - bullet->GetActorLocation();
			FVector currentFightDir = bullet->ProjectileMovementComponent->Velocity;

			float length = dir.Size();
			currentFightDir.Normalize();
			dir.Normalize();

			float dot = FVector::DotProduct(currentFightDir, dir);
			float sizeA = currentFightDir.Size();
			float sizeB = dir.Size();

			float denomenator = sizeA * sizeB;

			float angle = UKismetMathLibrary::Acos(dot / denomenator);

			angle = angle * (180 / 3.14159);



			if (angle > 0 && angle < bullet->HomingAngle)
			{
				if (closestPlayer == nullptr)
				{
					closestPlayer = actor;
					distance = length;
				}
				else
				{

					if (length < distance)//potentially rework to use sizesquared
					{
						closestPlayer = actor;
						distance = length;
					}

				}
			}

		}


		if (closestPlayer)
		{

			bullet->ProjectileMovementComponent->HomingTargetComponent = closestPlayer->GetRootComponent();
			UE_LOG(LogTemp, Warning, TEXT("Enemy Found"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Enemy Found"));
		}

	}


		
	

	
	
}