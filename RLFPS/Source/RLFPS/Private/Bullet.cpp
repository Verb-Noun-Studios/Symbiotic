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
			FVector currentFightDir = this->ProjectileMovementComponent->Velocity;

			float length = dir.Size();
			currentFightDir.Normalize();
			dir.Normalize();

			float dot = FVector::DotProduct(currentFightDir, dir);
			float sizeA = currentFightDir.Size();
			float sizeB = dir.Size();

			float denomenator = sizeA * sizeB;

			float angle = UKismetMathLibrary::Acos(dot / denomenator);
			
			angle = angle * (180 / 3.14159);

			
			
			if (angle > 0 && angle < HomingAngle && length < homingRange)
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
	}

	return closestPlayer;

}

bool ABullet::CheckTargetAngle() 
{

	FVector dir = target->GetActorLocation() - this->GetActorLocation();
	FVector currentFightDir = this->ProjectileMovementComponent->Velocity;

	float length = dir.Size();
	currentFightDir.Normalize();
	dir.Normalize();

	float dot = FVector::DotProduct(currentFightDir, dir);
	float sizeA = currentFightDir.Size();
	float sizeB = dir.Size();

	float denomenator = sizeA * sizeB;

	float angle = UKismetMathLibrary::Acos(dot / denomenator);

	angle = angle * (180 / 3.14159);

	//UE_LOG(LogTemp, Warning, TEXT("Length: %f    Range: %f   Angle: %f"), length, homingRange, angle);
	if (angle > HomingAngle || length > homingRange)
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