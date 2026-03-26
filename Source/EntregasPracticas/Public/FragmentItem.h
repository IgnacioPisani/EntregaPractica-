#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "FragmentItem.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFragmentCollected, FName, FragmentID);

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

	UPROPERTY(BlueprintAssignable)
	FOnFragmentCollected OnFragmentCollected;

protected:
	virtual void OnInteract(ACharacter* Character) override;
};