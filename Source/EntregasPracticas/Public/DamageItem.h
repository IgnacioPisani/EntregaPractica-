// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "DamageItem.generated.h"

/**
 * 
 */
UCLASS()
class ENTREGASPRACTICAS_API ADamageItem : public AItemBase
{
	GENERATED_BODY()

public:
	ADamageItem();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dano")
	float DamageAmount = 25.f;
 
protected:
	virtual void OnInteract(ACharacter* Character) override;
};
