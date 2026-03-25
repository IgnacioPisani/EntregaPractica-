// Fill out your copyright notice in the Description page of Project Settings.


#include "FragmentComponent.h"

// Sets default values for this component's properties
UFragmentComponent::UFragmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFragmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFragmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


bool UFragmentComponent::AddFragment(FName FragmentID)
{
	if (CollectedFragments.Contains(FragmentID))
	{
		UE_LOG(LogTemp, Warning, TEXT("[FragmentComponent] Fragmento '%s' ya fue recolectado."), *FragmentID.ToString());
		return false;
	}
 
	CollectedFragments.Add(FragmentID);
	OnFragmentAdded.Broadcast(FragmentID);
 
	UE_LOG(LogTemp, Log, TEXT("[FragmentComponent] Fragmento agregado: '%s' | Total: %d / %d"),
		*FragmentID.ToString(), CollectedFragments.Num(), RequiredFragments);
 
	if (IsArtifactComplete())
	{
		UE_LOG(LogTemp, Log, TEXT("[FragmentComponent] Artefacto completo!"));
		OnArtifactComplete.Broadcast();
	}
 
	return true;
}
 
bool UFragmentComponent::HasFragment(FName FragmentID) const
{
	return CollectedFragments.Contains(FragmentID);
}
 
bool UFragmentComponent::IsArtifactComplete() const
{
	return CollectedFragments.Num() >= RequiredFragments;
}