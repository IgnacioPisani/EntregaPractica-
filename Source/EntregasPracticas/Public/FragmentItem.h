#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "FragmentItem.generated.h"

class AFragmentItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFragmentItemCollected, AFragmentItem*, Item, FName, FragmentID);

UCLASS()
class ENTREGASPRACTICAS_API AFragmentItem : public AItemBase
{
	GENERATED_BODY()

public:
	AFragmentItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fragmento")
	FName FragmentID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fragmento")
	FText FragmentName;

	UPROPERTY(BlueprintAssignable, Category = "Eventos")
	FOnFragmentItemCollected OnFragmentItemCollected;

protected:
	virtual void OnInteract(ACharacter* Character) override;
};