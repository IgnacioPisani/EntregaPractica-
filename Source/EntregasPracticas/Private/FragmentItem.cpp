// Fill out your copyright notice in the Description page of Project Settings.


#include "FragmentItem.h"

#include "EntregasPracticasCharacter.h"
#include "FragmentComponent.h"

class UFragmentComponent;

AFragmentItem::AFragmentItem()
{
	FragmentID = NAME_None;
	FragmentName = FText::FromString(TEXT("Fragmento"));
}
 
void AFragmentItem::OnInteract(ACharacter* Character)
{
	UFragmentComponent* FragComp = Character->FindComponentByClass<UFragmentComponent>();
	if (!FragComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("[FragmentItem] El personaje no tiene FragmentComponent."));
		return;
	}
 
	FragComp->AddFragment(FragmentID);
 
	OnFragmentItemCollected.Broadcast(this, FragmentID);
	
	UE_LOG(LogTemp, Log, TEXT("[FragmentItem] Fragmento '%s' recolectado."), *FragmentID.ToString());
	DestroyItem();
}
 