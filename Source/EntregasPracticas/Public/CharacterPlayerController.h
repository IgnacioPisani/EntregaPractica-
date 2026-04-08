#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterPlayerController.generated.h"

class UInputMappingContext;
class AHealthModifier;
class UHealthWidget;
class UHealthComponent;

UCLASS()
class ENTREGASPRACTICAS_API ACharacterPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UHealthWidget> HealthWidgetClass;

	UPROPERTY()
	UHealthWidget* HealthWidget;

	UPROPERTY()
	AHealthModifier* HealthModifier;

	UFUNCTION()
	void HandleLifeChanged(float CurrentHealth, float MaxHealth);

	UFUNCTION()
	void HandleDeath();

	void BindToCharacter();

	UFUNCTION()
	void HandleHealthTick(int32 TickCount);

	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* DefaultMappingContext;
};