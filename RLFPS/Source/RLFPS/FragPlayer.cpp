// Fill out your copyright notice in the Description page of Project Settings.


#include "FragPlayer.h"
#include "FragPlayerCollisionComponent.h"
#include "FragMovementComponent.h"
#include "HealthComponent.h"
#include "Engine.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
// Sets default values
AFragPlayer::AFragPlayer()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		FName ID_Characters;
		FText NAME_Characters;
		FConstructorStatics()
			: ID_Characters(TEXT("Characters"))
			, NAME_Characters(NSLOCTEXT("SpriteCategory", "Characters", "Characters"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;
	// Create the player collision
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Player Collision"));
	Collider->InitBoxExtent(FVector(30.f, 30.f, 56.f));
	// Add physical reference to the player's forward vector
	PlayerForwardRefComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Player Forward"));
	if (PlayerForwardRefComponent)
		PlayerForwardRefComponent->SetupAttachment(Collider);
	// Add a helper
#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SpriteInfo.Category = ConstructorStatics.ID_Characters;
		ArrowComponent->SpriteInfo.DisplayName = ConstructorStatics.NAME_Characters;
		ArrowComponent->SetupAttachment(PlayerForwardRefComponent);
		ArrowComponent->bIsScreenSizeScaled = true;
	}
#endif
	// Initialize the camera
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(PlayerForwardRefComponent);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 56.f - 4.f));
	// Add the character collision and movement component
	CollisionComponent = CreateDefaultSubobject<UFragPlayerCollisionComponent>(TEXT("Defragr Character Collision"));
	MovementComponent = CreateDefaultSubobject<UFragMovementComponent>(TEXT("Defragr Character Movement"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Defragr Health Component"));
	if (CollisionComponent)
	{
		CollisionComponent->Player = this;
		CollisionComponent->MovementComponent = MovementComponent;
	}
	// Throw down the character movement
	if (MovementComponent)
	{
		MovementComponent->UpdatedComponent = Collider;
		MovementComponent->CollisionComponent = CollisionComponent;
		MovementComponent->Player = this;
	}
}
// Called to bind functionality to input
void AFragPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(InputComponent);
	// Set up movement
	InputComponent->BindAxis("MoveForward", this, &AFragPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFragPlayer::MoveRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFragPlayer::DoJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AFragPlayer::StopJump);
	// Set up mouse inputs
	InputComponent->BindAxis("Turn", this, &AFragPlayer::MouseX);
	InputComponent->BindAxis("LookUp", this, &AFragPlayer::MouseY);
}
// Called when the game starts or when spawned
void AFragPlayer::BeginPlay()
{
	Super::BeginPlay();

}
// Called every frame
void AFragPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Handles the input from mouse to control the camera
	UpdateViewingAngles();
	// After we decide where the player is facing, we get the forward vector
	// of the player for easy access.
	ForwardVector = PlayerForwardRefComponent->GetForwardVector();
	RightVector = PlayerForwardRefComponent->GetRightVector();
}
void AFragPlayer::SetPosition(FVector NewPosition)
{
	MovementComponent->origin = NewPosition;
}
FVector AFragPlayer::GetPosition()
{
	return MovementComponent->GetOrigin();
}
void AFragPlayer::SetVelocity(FVector NewVelocity)
{
	MovementComponent->playerVelocity = NewVelocity;
}
void AFragPlayer::SetRelativeVelocity(FVector NewVelocity)
{
	MovementComponent->playerVelocity = PlayerForwardRefComponent->GetRelativeTransform().TransformVector(NewVelocity);
}
FVector AFragPlayer::GetVelocity() const
{
	return this->MovementComponent->playerVelocity;
}
void AFragPlayer::SetRotation(FQuat NewRotation)
{
	// We only need the pitch of the camera since
	// the camera is attached to the player's body
	// and the body does the Z rotation
	
	FRotator NewCameraRotation(NewRotation);
	NewCameraRotation.Roll = 0.f;
	NewCameraRotation.Pitch = FMath::Clamp(NewCameraRotation.Pitch, -0.0f, 0.0f);
	FString pitchString = FString::SanitizeFloat(NewCameraRotation.Pitch);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Test"));
	NewCameraRotation.Yaw = 0.f;
	FirstPersonCameraComponent->SetRelativeRotation(NewCameraRotation);
	// Squash the roll and pitch of the rotation for the Z
	// rotation of the actual player.
	FRotator NewPlayerRotation(NewRotation);
	NewPlayerRotation.Roll = 0.f;
	NewPlayerRotation.Pitch = 0.f;
	PlayerForwardRefComponent->SetWorldRotation(NewPlayerRotation);
}

void AFragPlayer::AddRotation()
{
	
	FQuat newQuat(FMath::RandRange(xMin, xMax), FMath::FRandRange(yMin, yMax), FMath::FRandRange(zMin, zMax), 1.0f);
	FRotator RotationToAdd(newQuat);

	FirstPersonCameraComponent->AddLocalRotation(RotationToAdd);
}

FRotator AFragPlayer::GetRotation()
{
	return FirstPersonCameraComponent->GetComponentRotation();
}
float AFragPlayer::GetGroundSpeed()
{
	return MovementComponent->groundSpeed;
}
void AFragPlayer::DoJump()
{
	MovementComponent->CheckJump();
}
void AFragPlayer::StopJump()
{
	JumpInput = false;
}
void AFragPlayer::UpdateViewingAngles()
{
	// Pitch camera up and down
	if (FirstPersonCameraComponent)
	{
		FVector v(0.f, -MouseVelocity.Y * MouseSensitivity, 0.f);
		FirstPersonCameraComponent->AddLocalRotation(FQuat::MakeFromEuler(v));
		FMinimalViewInfo cameraViewInfo;
		FirstPersonCameraComponent->GetCameraView(1.0f, cameraViewInfo);
		if (cameraViewInfo.Rotation.Pitch > pitchMaxY) {
			FRotator temp(pitchMaxY * MouseSensitivity, cameraViewInfo.Rotation.Yaw, cameraViewInfo.Rotation.Roll);
			FirstPersonCameraComponent->SetWorldRotation(temp);
		}
		if (cameraViewInfo.Rotation.Pitch < pitchMinY) {
			FRotator temp(pitchMinY * MouseSensitivity, cameraViewInfo.Rotation.Yaw, cameraViewInfo.Rotation.Roll);
			FirstPersonCameraComponent->SetWorldRotation(temp);
		}
	}
	// Rotate the reference point component
	if (PlayerForwardRefComponent)
	{
		FVector v(0.f, 0.f, MouseVelocity.X * MouseSensitivity);
		PlayerForwardRefComponent->AddWorldRotation(FQuat::MakeFromEuler(v));
	}
}
void AFragPlayer::MoveForward(float Value)
{
		MovementInput.X = Value;
}
void AFragPlayer::MoveRight(float Value)
{
		MovementInput.Y = Value;
}
void AFragPlayer::MouseX(float Value)
{
	MouseVelocity.X = Value;
}
void AFragPlayer::MouseY(float Value)
{
	MouseVelocity.Y = Value;
}
FVector2D AFragPlayer::ConsumeMovementInput()
{
	FVector2D LastWishMove = MovementInput;
	MovementInput = FVector2D::ZeroVector;
	return LastWishMove;
}
FVector2D AFragPlayer::ConsumeMouseInput()
{
	FVector2D LastRelationalMousePos = MouseVelocity;
	MouseVelocity = FVector2D::ZeroVector;
	return MouseVelocity;
}


void AFragPlayer::dealDamage(float damage)
{
	currentHealth -= damage;
	if (currentHealth < 0.0f) currentHealth = 0.0f;
}