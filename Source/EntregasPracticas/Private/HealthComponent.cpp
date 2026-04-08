// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Health = 100.f;
	MaxHealth = 100.f;
	MinHealth = 0.f;
	SetIsReplicatedByDefault(true);
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
void UHealthComponent::ModifyHealth(float Delta)
{

	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, MinHealth, MaxHealth);

	if (Health != OldHealth && GetOwner()->HasAuthority())
	{
		OnLifeChanged.Broadcast(Health, MaxHealth);
	}
	
}

void UHealthComponent::OnRep_Health()
{
	OnLifeChanged.Broadcast(Health, MaxHealth);
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UHealthComponent, Health);
}
