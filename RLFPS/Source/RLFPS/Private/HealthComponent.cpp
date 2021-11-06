// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100;
	currentHealth = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0) 
	{
		//endGame
	}

	currentHealth = FMath::Clamp(currentHealth - Damage, 0.0f, DefaultHealth);
}

void UHealthComponent::InflictDamage(float Damage) 
{
	currentHealth = FMath::Clamp(currentHealth - Damage, 0.0f, DefaultHealth);
}

void UHealthComponent::Heal(float HP)
{
	currentHealth = FMath::Clamp(currentHealth + HP, 0.0f, DefaultHealth);
}


