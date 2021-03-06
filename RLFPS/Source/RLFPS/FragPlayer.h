// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FragPlayer.generated.h"

class UFragMovementComponent;
class UFragPlayerCollisionComponent;
class UBoxComponent;
class UArrowComponent;
class UCameraComponent;
class UHealthComponent;

UCLASS(config = Game, BlueprintType, hideCategories = ("Pawn|fragCharacter|InternalEvents"), meta = (ShortTooltip = "Custom character specifically built for Q3 movement."))
class RLFPS_API AFragPlayer : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	AFragPlayer();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	/** Called when the controller sets up the input for the pawn */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	/** Per frame tick */
	virtual void Tick(float Delta);
	/** Holds the controller that's possessing this character */
	AController* Controller;
	//Movement Component Parts
public:
	/* Sets the position of the player */
	UFUNCTION(BlueprintCallable, Category = "fragCharacter")
		void SetPosition(FVector NewPosition);
	/* Gets the position of the player */
	UFUNCTION(BlueprintCallable, Category = "fragCharacter")
		FVector GetPosition();
	/* Sets the velocity of the player */
	UFUNCTION(BlueprintCallable, Category = "fragCharacter")
		void SetVelocity(FVector NewVelocity);
	/* Sets the velocity in relation to the player */
	UFUNCTION(BlueprintCallable, Category = "fragCharacter")
		void SetRelativeVelocity(FVector NewVelocity);
	virtual FVector GetVelocity() const override;
	/* Sets the player's viewing angles */
	UFUNCTION(BlueprintCallable, Category = "fragCharacter")
		void SetRotation(FQuat NewRotation);
	
	UFUNCTION(BlueprintCallable, Category = "fragCharacter")
		void UpdateControls(bool rightHanded);

	/* Gets the player's viewing angles */
	UFUNCTION(BlueprintCallable, Category = "fragCharacter")
		FRotator GetRotation();
	/* Get the player's linear speed */
	UFUNCTION(BlueprintCallable, Category = "fragCharacter")
		float GetGroundSpeed();
	/* Commit to a jump */
	UFUNCTION(BlueprintCallable, Category = "fragCharacter|CharacterMovement")
		virtual void DoJump();
	UFUNCTION(BlueprintCallable, Category = "fragCharacter|CharacterMovement")
		virtual void StopJump();
public:
	/* The local normalized forward vector of the player's facing angle */
	UPROPERTY(Category = Transform, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FVector ForwardVector;
	/* The local normalized right vector of the player's facing angle */
	UPROPERTY(Category = Transform, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FVector RightVector;
	/* X is forward [W] and back [S] (1.0 to -1.0) and Y is right [D] and left [A] (1.0 to - 1.0) */
	UPROPERTY(Category = Input, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FVector2D MovementInput;
	UPROPERTY(Category = Input, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool JumpInput;

	/* Stores relational (to last frame) mouse position */
	FVector2D MouseVelocity;

	UPROPERTY(Category = Input, EditAnywhere, BlueprintReadWrite)
		float MouseSensitivity;
	UPROPERTY(Category = Input, EditAnywhere, BlueprintReadWrite)
		bool LeftHanded;

	//Handles the Collision Component
public:
	/** The BoxComponent being used for movement collision. Always treated as being vertically aligned in simple collision check functions */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* Collider;
	/** Character's movement component */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UFragMovementComponent* MovementComponent;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UFragPlayerCollisionComponent* CollisionComponen;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USceneComponent* PlayerForwardRefComponent;
	/** Helper object to see which direction is forward */
#if WITH_EDITORONLY_DATA
	UPROPERTY()
		UArrowComponent* ArrowComponent;
#endif
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

	/** Set the Max Pitch For Camera */
	UPROPERTY(Category = "Camera ", EditAnywhere, BlueprintReadWrite)
		float pitchMaxY;
	/** Set the Min Pitch For Camera */
	UPROPERTY(Category = "Camera ", EditAnywhere, BlueprintReadWrite)
		float pitchMinY;




	//Camera Pieces
public:
	/** Takes mouse input and converts it into camera rotational movements */
	void UpdateViewingAngles();
	/** Handles moving forward/backward */
	void MoveForward(float Value);
	/** Handles strafing movement, left and right */
	void MoveRight(float Value);
	/** Mouse movement input callbacks */
	void MouseX(float Value);
	void MouseY(float Value);
	/**
	 * Gets and immediately consumes the movement input where
	 * X is forward [W] and back [S] (1.0 to -1.0) and Y is right [D] and left [A] (1.0 to - 1.0)
	 */
	FVector2D ConsumeMovementInput();
	/** Gets and immediately consumes mouse input */
	FVector2D ConsumeMouseInput();

};
