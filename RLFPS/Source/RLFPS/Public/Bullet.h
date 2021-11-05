// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Gun.h"
#include "Bullet.generated.h"

UCLASS()
class RLFPS_API ABullet : public AActor
{
	GENERATED_BODY()



	

public:	
	// Sets default values for this actor's properties
	ABullet();
	UFUNCTION(BlueprintCallable)
	void SetInitialDirection(FVector dir);
	UFUNCTION(BlueprintCallable)
	void SetInitialSpeed(float Speed);
	UFUNCTION(BlueprintCallable)
	void SetGun(AGun* newGun);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	AGun* gun;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	// Used to increase the speed, 1 is normal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float fireSpeedMultipler;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Homing)
	TSubclassOf<AActor> playerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Homing)
	TSubclassOf<AActor> targetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Homing)
	AActor* target;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Homing)
		float HomingStrength = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Homing)
	float initialHomingStrength = 1000.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Homing)
	float HomingStackingStrength = 500.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Homing)
	float homingRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Homing)
	float initialHomingRange = 500.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Homing)
	float HomingRangeStackingStrength = 250.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Homing)
		float HomingAngle = 0.1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Homing)
		float lifeTime = 5.0;

	FVector DirectionOfFire;
	AActor* GetClosestActor();
	bool CheckTargetAngle();
	UFUNCTION(BlueprintCallable)
	float GetDistanceToTarget();


};
