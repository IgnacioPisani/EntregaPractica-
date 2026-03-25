// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
 
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}
 
void AItemBase::Interact_Implementation(ACharacter* Character)
{
	if (!Character) return;
	OnInteract(Character);
}
 
void AItemBase::DestroyItem()
{
	Destroy();
}
 