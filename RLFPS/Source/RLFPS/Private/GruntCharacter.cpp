// Fill out your copyright notice in the Description page of Project Settings.


#include "GruntCharacter.h"
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AGruntCharacter::AGruntCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Defragr Health Component"));


	// (thornton) hack to make not spawn inside floor
	GetRootComponent()->AddLocalOffset(FVector::UpVector * GetCapsuleComponent()->GetScaledCapsuleHalfHeight());


	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetClass()->GetDefaultObject()->GetName());
}

// Called when the game starts or when spawned
void AGruntCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGruntCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < statusEffects.Num(); i++)
	{
		UStatusEffect* effect = statusEffects[i];

		if (effect->dead)
		{
			effect->OnDestroy(this);
			statusEffects.Remove(effect);
			effect->ConditionalBeginDestroy();
			UpdateStatusEffects();
		}
		else
		{
			effect->OnTick(this, DeltaTime);
			effect->OnTick_Implementation(this, DeltaTime);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(effect->name.ToString()));
		}
		
	}

}

void AGruntCharacter::AddEffect(UStatusEffect* newEffect)
{
	for (UStatusEffect* effect : statusEffects)
	{
		if (newEffect->name == effect->name)
		{
			effect->stacks++;
			effect->timeRemaining = effect->duration;
			newEffect->ConditionalBeginDestroy();
			UpdateStatusEffects();
			return;
		}
	}
	newEffect->owner = this;

	statusEffects.Add(newEffect);
	newEffect->OnStart(this);
	UpdateStatusEffects();
	UE_LOG(LogTemp, Warning, TEXT("AddingEffect: %s"), *(newEffect->name.ToString()));
}

void AGruntCharacter::OnDeath()
{
	if (EnemySpawner)
	{
		EnemySpawner->emnemiesKilled++;
	}
}