// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "GameFramework/Actor.h"
#include "ArtifactAssembler.generated.h"

UCLASS()
class ENTREGASPRACTICAS_API AArtifactAssembler : public AActor, public IInteract
{
	GENERATED_BODY()
	
public:
	AArtifactAssembler();
 
	virtual void Interact_Implementation(ACharacter* Character) override;
 
protected:
	virtual void BeginPlay() override;
 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes")
	UStaticMeshComponent* Mesh;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembler")
	TSubclassOf<AActor> ActorToSpawn;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembler")
	float AssembleDelay = 3.f;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembler")
	FVector SpawnOffset = FVector(0.f, 0.f, 100.f);
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembler")
	UMaterialInterface* ActiveMaterial;
 
private:
	int32 TotalFragments = 0;
	int32 CollectedFragments = 0;
	bool bReady = false;
	bool bAssembling = false;
 
	FTimerHandle AssembleTimerHandle;
 
	UFUNCTION()
	void OnFragmentCollected( FName FragmentID);
 
	void CheckCompletion();
	void SetReady();
 
	UFUNCTION()
	void ExecuteAssemble();
};
 