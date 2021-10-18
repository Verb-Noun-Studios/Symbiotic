// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 30000.0f;
		ProjectileMovementComponent->MaxSpeed = 30000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.05f;
	}
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (ProjectileMovementComponent->bIsHomingProjectile)
	{
		//|| target->IsActorBeingDestroyed() || !target->IsValidLowLevel()
		if (target == nullptr || CheckTargetAngle())
		{
			target = GetClosestActor();
			if (target)
			{

				ProjectileMovementComponent->HomingTargetComponent = target->GetRootComponent();

			}
			
		}
		else 
		{

			float multiplier = (1 + (1 - (GetDistanceToTarget() / homingRange)));

			UE_LOG(LogTemp, Warning, TEXT("Multiplier: %f"), multiplier);
			ProjectileMovementComponent->HomingAccelerationMagnitude = HomingStrength * multiplier;

		}
		
	}

	lifeTime = lifeTime - DeltaTime;

	if (lifeTime <= 0)
	{
		Destroy();
	}

}

void ABullet::SetInitialDirection(FVector dir)
{
	ProjectileMovementComponent->Velocity = dir * ProjectileMovementComponent->InitialSpeed * fireSpeedMultipler;
	DirectionOfFire = dir;
}

void ABullet::SetInitialSpeed(float speed)
{
	ProjectileMovementComponent->InitialSpeed = speed;
}

void ABullet::SetGun(AGun* newGun) 
{ 
	gun = newGun; 
}

AActor* ABullet::GetClosestActor()
{

	TArray<AActor*> enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), targetClass, enemies);
	AActor* closestPlayer = nullptr;
	float distance = INT_MAX;

	//log all actors found for debugging
	for (AActor* actor : enemies)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Names: %s"), *actor->GetName());
	}

	for (AActor* actor : enemies)
	{
		if (actor != this)
		{
			FVector dir = actor->GetActorLocation() - this->GetActorLocation();

			float dot = FVector::DotProduct(DirectionOfFire, dir);
			float sizeA = DirectionOfFire.Size();
			float sizeB = dir.Size();

			float denomenator = sizeA * sizeB;

			float angle = UKismetMathLibrary::Acos(dot / denomenator);
			
			UE_LOG(LogTemp, Warning, TEXT("Angle: %f"), angle);
			if (angle > 0 && angle < HomingAngle && dir.Size() < homingRange)
			{
				if (closestPlayer == nullptr)
				{
					closestPlayer = actor;
					distance = dir.Size();
				}
				else
				{
								
					if (dir.Size() < distance)//potentially rework to use sizesquared
					{
						closestPlayer = actor;
						distance = dir.Size();
					}				
				
				}
			}
		}
	}

	return closestPlayer;

}

bool ABullet::CheckTargetAngle() 
{
	FVector dir = target->GetActorLocation() - this->GetActorLocation();

	float dot = FVector::DotProduct(DirectionOfFire, dir);
	float sizeA = DirectionOfFire.Size();
	float sizeB = dir.Size();

	float denomenator = sizeA * sizeB;

	float angle = UKismetMathLibrary::Acos(dot / denomenator);


	if (angle > HomingAngle || dir.Size() > homingRange)
	{
		return true;
	}
	
	return false;
}


float ABullet::GetDistanceToTarget() 
{
	FVector dir = target->GetActorLocation() - this->GetActorLocation();
	return dir.Size();
}