// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "FragMovementComponent.generated.h"

class AFragPlayer;
class UFragPlayerCollisionComponent;

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Fly,
	Spectate,
	Normal
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RLFPS_API UFragMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
public:
	UFragMovementComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	AFragPlayer* Player;
	UFragPlayerCollisionComponent* CollisionComponent;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	float delta;
	FVector2D wishMove;
	bool wishJump;
	UPROPERTY(BlueprintReadOnly)
	FVector	playerVelocity;
	bool isGrounded;
	FVector origin = FVector::ZeroVector;
	FVector GroundVelocity = FVector::ZeroVector;
	float groundSpeed = 0.8f;
	EMovementType MovementType = EMovementType::Normal;
public:
	/** Custom gravity scale. Gravity is multiplied by this amount for the character */
	UPROPERTY(Category = "General Movement", EditAnywhere, BlueprintReadWrite)
		float Gravity = 20.f;
	/** Amount of jumping force the player has, does not represent absolute jump height */
	UPROPERTY(Category = "General Movement", EditAnywhere, BlueprintReadWrite)
		float JumpForce = 8.f;
	/** Ground friction */
	UPROPERTY(Category = "General Movement", EditAnywhere, BlueprintReadWrite)
		float Friction = 6.f;
	/** The rate at which the player stops when on the ground */
	UPROPERTY(Category = "Ground Movement", EditAnywhere, BlueprintReadWrite)
		float GroundStopSpeed = 100.f;
	/** The maximum speed the player can travel while on the ground */
	UPROPERTY(Category = "Ground Movement", EditAnywhere, BlueprintReadWrite)
		float GroundMaxSpeed = 8.f;
	/** The rate at which the player gains speed while on the ground */
	UPROPERTY(Category = "Ground Movement", EditAnywhere, BlueprintReadWrite)
		float GroundAcceleration = 15.0f;
	/** The rate at which the player loses speed while on the ground */
	UPROPERTY(Category = "Ground Movement", EditAnywhere, BlueprintReadWrite)
		float GroundDampening = 8.f;

	/** How Many times the player can jump before having to be grouned again*/
	UPROPERTY(Category = "Air Movement", EditAnywhere, BlueprintReadWrite)
		int MaxJumps = 2;

	/** Tracker for how many times the player has jumped before touching grouned again*/
	UPROPERTY(Category = "Air Movement", EditAnywhere, BlueprintReadWrite)
		int JumpCount = 2;

	/** The maximum speed the player can achieve while not strafe jumping */
	UPROPERTY(Category = "Air Movement", EditAnywhere, BlueprintReadWrite)
		float AirMaxSpeed = 7.f;
	/**  */
	UPROPERTY(Category = "Air Movement", EditAnywhere, BlueprintReadWrite)
		float AirStopAccelerate = 2.5f;
	/** The maximum speed the player can achieve when strafing, but not actually strafe jumping */
	UPROPERTY(Category = "Air Movement", EditAnywhere, BlueprintReadWrite)
		float AirStrafeSpeed = 4.f;
	/** The rate at which the player gains speed to achieve Air Strafe Speed */
	UPROPERTY(Category = "Air Movement", EditAnywhere, BlueprintReadWrite)
		float AirStrafeAcceleration = 10.f;
	/** The amount of air control the player has */
	UPROPERTY(Category = "Air Movement", EditAnywhere, BlueprintReadWrite)
		float CPMAirControl = 2.f;
	/* Friction for spectator modes */
	UPROPERTY(Category = "General Movement", EditAnywhere, BlueprintReadWrite)
		float SpectatorFriction = 6.f;
	UPROPERTY(Category = "General Movement", EditAnywhere, BlueprintReadWrite)
		float SpectatorAccelerate = 10.f;
	UPROPERTY(Category = "General Movement", EditAnywhere, BlueprintReadWrite)
		float SpectatorStopSpeed = 100.f;
public:
	void PlayerMoveSingle();
	void GroundMove();
	void ApplyFriction();
	void AirMove();
	bool CheckJump();
	void QueueJump();
	void FlyMove();
	UFUNCTION(BlueprintCallable)
	void ApplyAcceleration(FVector WishDirection, float WishSpeed, float DynamicAcceleration);
	void AirControl(FVector WishDirection, float WishSpeed);
	void ApplyGravity();
	float CmdScale();
	void ClipVelocity(FVector In, FVector Normal, FVector& Out, float Overbounce);
public:
	void SetOrigin(FVector Position);
	FVector GetOrigin();
	
};
