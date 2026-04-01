#include "HealthModifier.h"
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

	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AHealthModifier::OnOverlapBegin);
	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &AHealthModifier::OnOverlapEnd);
}

void AHealthModifier::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
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

void AHealthModifier::OnOverlapEnd(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor == AffectedActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor salio de zona"));

		GetWorld()->GetTimerManager().ClearTimer(EffectTimer);
		AffectedActor = nullptr;
	}
}

#include "HealthInterface.h"

void AHealthModifier::ApplyEffect()
{
	if (!AffectedActor) return;

	TickCounter++;

	float FinalAmount = bIsHealing ? Amount : -Amount;

	UE_LOG(LogTemp, Warning, TEXT("Aplicando %s: %f (Tick %d)"),
		bIsHealing ? TEXT("Curacion") : TEXT("Daño"),
		FinalAmount,
		TickCounter);

	// 🔥 Aplicar efecto usando la interfaz
	if (AffectedActor->GetClass()->ImplementsInterface(UHealthInterface::StaticClass()))
	{
		IHealthInterface::Execute_ModifyHealth(AffectedActor, FinalAmount);

		UE_LOG(LogTemp, Warning, TEXT("ModifyHealth ejecutado correctamente"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("El actor no implementa HealthInterface"));
	}

	// 🔥 Evento para contar ticks
	OnHealthTick.Broadcast(TickCounter);
}