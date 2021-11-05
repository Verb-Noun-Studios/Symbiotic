// Fill out your copyright notice in the Description page of Project Settings.

#include "FragMovementComponent.h"
#include "FragPlayer.h"
#include "FragPlayerCollisionComponent.h"
#include "Engine.h"
UFragMovementComponent::UFragMovementComponent(const FObjectInitializer& ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}
void UFragMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	origin = Player->GetTransform().GetLocation();
}
void UFragMovementComponent::ApplyFriction()
{
	float speed;
	float newSpeed;
	float control;
	float drop = 0.0f;
	speed = playerVelocity.Size();
	if (CollisionComponent->IsGrounded)
	{
		control = speed < GroundAcceleration ? GroundDampening : speed;
		drop = control * Friction * delta;
	}
	if (MovementType == EMovementType::Spectate)
		drop += speed * SpectatorFriction * delta;
	newSpeed = speed - drop;
	if (newSpeed < 0.f)
		newSpeed = 0.f;
	if (speed > 0.f)
		newSpeed /= speed;
	playerVelocity.X *= newSpeed;
	playerVelocity.Y *= newSpeed;
}
void UFragMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	delta = DeltaTime;
	if (Player)
	{
		// Grab the input from the player
		wishMove = Player->ConsumeMovementInput();
		if (MovementType == EMovementType::Spectate)
		{
			FlyMove();
			Player->Collider->SetWorldLocation(origin);
			return;
		}
		//QueueJump();
		CollisionComponent->TraceGround();
		if (CollisionComponent->CanGroundMove) {
			GroundMove();
			JumpCount = 2;
		}
		else
			AirMove();
		CollisionComponent->TraceGround();
		// Record the ground velocity and speed of the player
		GroundVelocity.X = playerVelocity.X;
		GroundVelocity.Y = playerVelocity.Y;
		groundSpeed = GroundVelocity.Size();
		Player->Collider->SetWorldLocation(origin);
		// Logs
		//GEngine->AddOnScreenDebugMessage(20, 0.01f, FColor::Red, FString::Printf(TEXT("Position [X: %.6f, Y: %.6f, Z: %.6f]"), GetOrigin().X, GetOrigin().Y, GetOrigin().Z));
		//GEngine->AddOnScreenDebugMessage(2, 0.01f, FColor::Green, FString::Printf(TEXT("Is Grounded [%d]"), CollisionComponent->IsGrounded));
		//GEngine->AddOnScreenDebugMessage(0, 0.01f, FColor::Green, FString::Printf(TEXT("Desired Velocity [X: %.2f, Y: %.2f, Z: %.2f]"), playerVelocity.X, playerVelocity.Y, playerVelocity.Z));
		//GEngine->AddOnScreenDebugMessage(1, 0.01f, FColor::Green, FString::Printf(TEXT("Desired Linear Speed [%.2fups]"), groundSpeed));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 0.01f, FColor::Red, TEXT("NO OWNER"));
	}
}
void UFragMovementComponent::GroundMove()
{
	
	ApplyFriction();
	FVector wishDirection;
	FVector wishvel = FVector::ZeroVector;
	FVector TransformForward = Player->ForwardVector;
	FVector TransformRight = Player->RightVector;
	wishvel.X = TransformForward.X * wishMove.X + TransformRight.X * wishMove.Y;
	wishvel.Y = TransformForward.Y * wishMove.X + TransformRight.Y * wishMove.Y;
	wishvel.Z = TransformForward.Z * wishMove.X + TransformRight.Z * wishMove.Y;
	wishDirection = wishvel;
	float wishSpeed = wishDirection.Size();
	wishDirection.Normalize();
	wishSpeed *= GroundMaxSpeed;
	ApplyAcceleration(wishDirection, wishSpeed, GroundAcceleration);
	float vel = playerVelocity.Size();
	ClipVelocity(playerVelocity, CollisionComponent->GroundTrace.ImpactNormal, playerVelocity, CollisionComponent->Overclip);
	playerVelocity.Normalize();
	playerVelocity *= vel;
	// Don't do anything if standing still
	if (playerVelocity.X == 0.f && playerVelocity.Y == 0.f)
		return;
	CollisionComponent->StepSlideMove(false);
}
void UFragMovementComponent::AirMove()
{
	GEngine->AddOnScreenDebugMessage(25, 0.01f, FColor::Red, FString::Printf(TEXT("AirBorn")));
	FVector wishDirection;
	FVector currentVelocity;
	float dynamicAcceleration;
	//ApplyFriction();
	// Set target direction for the character body to its inital state.
	wishDirection.X = Player->ForwardVector.X * wishMove.X + Player->RightVector.X * wishMove.Y;
	wishDirection.Y = Player->ForwardVector.Y * wishMove.X + Player->RightVector.Y * wishMove.Y;
	wishDirection.Z = 0.f;
	float wishSpeed = wishDirection.Size();
	wishDirection.Normalize();
	wishSpeed *= AirMaxSpeed;
	// CPM: Aircontrol
	float wishSpeed2 = wishSpeed;
	if (FVector::DotProduct(playerVelocity, wishDirection) < 0)
		dynamicAcceleration = AirStopAccelerate;
	if (wishSpeed > AirStrafeSpeed)
		wishSpeed = AirStrafeSpeed;
		
	dynamicAcceleration = AirStrafeAcceleration;
	ApplyAcceleration(wishDirection, wishSpeed, dynamicAcceleration);
	AirControl(wishDirection, wishSpeed);
	// Apply gravity
	playerVelocity.Z -= Gravity * delta;
	CollisionComponent->StepSlideMove(true);
}
void UFragMovementComponent::AirControl(FVector WishDirection, float WishSpeed)
{
	float	zspeed, speed, dot, k;
	// Can't control movement if not moving forward or backward
	zspeed = playerVelocity.Z;
	playerVelocity.Z = 0;
	speed = playerVelocity.Size();
	playerVelocity.Normalize();
	dot = FVector::DotProduct(playerVelocity, WishDirection);
	k = 32.f;
	k *= CPMAirControl * dot * dot * delta;
	playerVelocity.X = playerVelocity.X * speed + WishDirection.X * k;
	playerVelocity.Y = playerVelocity.Y * speed + WishDirection.Y * k;
	playerVelocity.Normalize();
	playerVelocity.X *= speed;
	playerVelocity.Y *= speed;
	playerVelocity.Z = zspeed;
}
void UFragMovementComponent::ApplyAcceleration(FVector WishDirection, float WishSpeed, float DynamicAcceleration)
{
	float AddSpeed;
	float AccelerationSpeed;
	float CurrentSpeed;
	CurrentSpeed = FVector::DotProduct(WishDirection, playerVelocity);
	AddSpeed = WishSpeed - CurrentSpeed;
	if (AddSpeed <= 0.f)
		return;
	AccelerationSpeed = DynamicAcceleration * delta * WishSpeed;
	if (AccelerationSpeed > AddSpeed)
		AccelerationSpeed = AddSpeed;
	playerVelocity.X += AccelerationSpeed * WishDirection.X;
	playerVelocity.Y += AccelerationSpeed * WishDirection.Y;
	playerVelocity.Z += AccelerationSpeed * WishDirection.Z;
}
void UFragMovementComponent::FlyMove()
{
	float	speed, drop, friction, control, newspeed;
	FVector		wishvel;
	float		fmove, smove;
	FVector		wishdir;
	float		wishspeed;
	//	float		scale;
		// Set the view height
		//pm->ps->viewheight = DEFAULT_VIEWHEIGHT;
		// friction
	speed = playerVelocity.Size();
	if (speed < 1)
	{
		playerVelocity = FVector::ZeroVector;
	}
	else
	{
		drop = 0;
		friction = Friction * 1.5;	// extra friction
		control = speed < SpectatorStopSpeed ? SpectatorStopSpeed : speed;
		drop += control * friction * delta;
		// scale the velocity
		newspeed = speed - drop;
		if (newspeed < 0)
			newspeed = 0;
		newspeed /= speed;
		playerVelocity *= newspeed;
	}
	// accelerate
	//scale = PM_CmdScale(&pm->cmd);
	fmove = wishMove.X;
	smove = wishMove.Y;
	wishvel.X = Player->ForwardVector.X * fmove + Player->RightVector.X * smove;
	wishvel.Y = Player->ForwardVector.Y * fmove + Player->RightVector.Y * smove;
	wishvel.Z += 0.f;
	wishdir = wishvel;
	wishspeed = wishdir.Size();
	wishdir.Normalize();
	wishspeed *= 1000.f;
	ApplyAcceleration(wishdir, wishspeed, SpectatorAccelerate);
	// move
	Player->CollisionComponent->VectorMA(GetOrigin(), delta, playerVelocity, origin);
	//origin.Z = 0.f;
}
bool UFragMovementComponent::CheckJump()
{
	if (JumpCount != 0) {
		playerVelocity.Z = JumpForce;
		AirMove();
		JumpCount--;
	}
	if (wishJump)
	{
		//Set Up Sounds		
		//Player->PlayJumpSound();
		wishJump = false;
		return true;
	}
	return false;
}
void UFragMovementComponent::QueueJump()
{
	if (JumpCount != 0) 
	{
		wishJump = true;
		JumpCount--;
	}
}
float UFragMovementComponent::CmdScale()
{
	int		max;
	float	total;
	float	scale;
	max = abs(wishMove.X);
	if (abs(wishMove.Y) > max) {
		max = abs(wishMove.Y);
	}
	/*if (abs(cmd->upmove) > max) {
		max = abs(cmd->upmove);
	}*/
	if (!max) {
		return 0;
	}
	total = sqrt(wishMove.X * wishMove.X + wishMove.Y * wishMove.Y);
	scale = (float)groundSpeed * max / (127.0 * total);
	return scale;
}
void UFragMovementComponent::ClipVelocity(FVector In, FVector Normal, FVector& Out, float Overbounce)
{
	float Backoff = FVector::DotProduct(In, Normal);
	if (Backoff < 0.f)
		Backoff *= Overbounce;
	else
		Backoff /= Overbounce;
	Out.X = In.X - (Normal.X * Backoff);
	Out.Y = In.Y - (Normal.Y * Backoff);
	Out.Z = In.Z - (Normal.Z * Backoff);
}
void UFragMovementComponent::SetOrigin(FVector Position)
{
	origin = Position;
}
FVector UFragMovementComponent::GetOrigin()
{
	return origin;
}