#include "HealthModifier.h"

#include "HealthComponent.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

AHealthModifier::AHealthModifier()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
	RootComponent = TriggerZone;

	TriggerZone->SetCollisionProfileName(TEXT("Trigger"));
}

void AHealthModifier::BeginPlay()
{
	Super::BeginPlay();
}

void AHealthModifier::ApplyEffect()
{
	if (!AffectedActor) return;

	TickCounter++;

	float FinalAmount = bIsHealing ? Amount : -Amount;

	UE_LOG(LogTemp, Warning, TEXT("Aplicando %s: %f (Tick %d)"),
		bIsHealing ? TEXT("Curacion") : TEXT("Daño"),
		FinalAmount,
		TickCounter);

	UHealthComponent* HealthComp = AffectedActor->FindComponentByClass<UHealthComponent>();

	if (HealthComp)
	{
		HealthComp->ModifyHealth(FinalAmount);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("El actor no tiene HealthComponent"));
	}

	OnHealthTick.Broadcast(TickCounter);
}

void AHealthModifier::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (!OtherActor || OtherActor == this) return;

	UE_LOG(LogTemp, Warning, TEXT("Actor entro a zona"));

	AffectedActor = OtherActor;
	TickCounter = 0;

	GetWorld()->GetTimerManager().SetTimer(
		EffectTimer,
		this,
		&AHealthModifier::ApplyEffect,
		Interval,
		true
	);
}

void AHealthModifier::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (OtherActor == AffectedActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor salio de zona"));

		GetWorld()->GetTimerManager().ClearTimer(EffectTimer);
		AffectedActor = nullptr;
	}
}
