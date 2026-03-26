// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FragmentComponent.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFragmentAdded, FName, FragmentID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnArtifactComplete);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENTREGASPRACTICAS_API UFragmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFragmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Fragmentos")
	FOnFragmentAdded OnFragmentAdded;
 
	UPROPERTY(BlueprintAssignable, Category = "Fragmentos")
	FOnArtifactComplete OnArtifactComplete;
 
	UFUNCTION(BlueprintCallable, Category = "Fragmentos")
	bool AddFragment(FName FragmentID);
 
	UFUNCTION(BlueprintPure, Category = "Fragmentos")
	bool HasFragment(FName FragmentID) const;
 
	UFUNCTION(BlueprintPure, Category = "Fragmentos")
	int32 GetFragmentCount() const { return CollectedFragments.Num(); }
 
	UFUNCTION(BlueprintPure, Category = "Fragmentos")
	bool IsArtifactComplete() const;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fragmentos")
	int32 RequiredFragments = 3;
 
	UFUNCTION(BlueprintPure, Category = "Fragmentos")
	TArray<FName> GetCollectedFragments() const { return CollectedFragments; }
 
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fragmentos")
	TArray<FName> CollectedFragments;
		
};
