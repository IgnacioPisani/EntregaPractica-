// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageItem.h"
#include "EntregasPracticasCharacter.h"
#include "Kismet/GameplayStatics.h"

ADamageItem::ADamageItem()
{
}

void ADamageItem::OnInteract(ACharacter* Character)
{
	Super::OnInteract(Character);

	if (!Character) return;

	UGameplayStatics::ApplyDamage(
		Character,
		DamageAmount,
		nullptr,        // Instigator Controller
		this,           // Damage Causer
		nullptr         // Damage Type
	);
}