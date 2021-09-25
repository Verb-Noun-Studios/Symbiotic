// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Bullet.generated.h"

UCLASS()
class RLFPS_API ABullet : public AActor
{
	GENERATED_BODY()



	

public:	
	// Sets default values for this actor's properties
	ABullet();
	void SetInitialDirection(FVector dir);
	void SetInitialSpeed(float Speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float lifeTime = 5.0;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

};
