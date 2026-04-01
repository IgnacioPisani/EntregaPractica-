#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "HealthModifier.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthTick, int32, TickCount);

UCLASS()
class ENTREGASPRACTICAS_API AHealthModifier : public AActor
{
	GENERATED_BODY()
	
public:	
	AHealthModifier();

protected:
	virtual void BeginPlay() override;

	// 🔹 Zona de efecto
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerZone;

	// 🔹 Configuración
	UPROPERTY(EditAnywhere, Category="Health")
	float Amount = 10.f;

	UPROPERTY(EditAnywhere, Category="Health")
	float Interval = 1.0f;

	UPROPERTY(EditAnywhere, Category="Health")
	bool bIsHealing = false;

	// 🔹 Timer
	FTimerHandle EffectTimer;

	// 🔹 Actor afectado
	UPROPERTY()
	AActor* AffectedActor;

	// 🔹 Contador
	int32 TickCounter = 0;

	// 🔹 Eventos
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	void ApplyEffect();

public:

	// 🔥 Evento para Blueprint
	UPROPERTY(BlueprintAssignable)
	FOnHealthTick OnHealthTick;
};