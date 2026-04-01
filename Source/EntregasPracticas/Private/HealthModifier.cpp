#include "HealthModifier.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "HealthInterface.h"

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

	if (AffectedActor->Implements<UHealthInterface>())
	{
		IHealthInterface::Execute_ModifyHealth(AffectedActor, FinalAmount);

		UE_LOG(LogTemp, Warning, TEXT("ModifyHealth ejecutado correctamente"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("El actor no implementa HealthInterface"));
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
