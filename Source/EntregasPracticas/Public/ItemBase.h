// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class ENTREGASPRACTICAS_API AItemBase : public AActor, public IInteract
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
public:
	AItemBase();
 
	virtual void Interact_Implementation(ACharacter* Character) override;
 
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes")
	UStaticMeshComponent* Mesh;
 
	// Subclases definen el efecto usando el Character recibido
	virtual void OnInteract(ACharacter* Character) {}
 
	void DestroyItem();
};
 