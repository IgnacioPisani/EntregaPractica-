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

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerZone;

	UPROPERTY(EditAnywhere, Category="Health")
	float Amount = 10.f;

	UPROPERTY(EditAnywhere, Category="Health")
	float Interval = 1.0f;

	UPROPERTY(EditAnywhere, Category="Health")
	bool bIsHealing = false;

	FTimerHandle EffectTimer;

	UPROPERTY()
	AActor* AffectedActor;

	int32 TickCounter = 0;
	
	void ApplyEffect();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
public:

	UPROPERTY(BlueprintAssignable)
	FOnHealthTick OnHealthTick;
};