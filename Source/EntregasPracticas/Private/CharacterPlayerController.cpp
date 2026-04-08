#include "CharacterPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "HealthWidget.h"
#include "HealthComponent.h"
#include "EntregasPracticasCharacter.h"
#include "HealthModifier.h"
#include "Kismet/GameplayStatics.h"

class UEnhancedInputLocalPlayerSubsystem;

void ACharacterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController()) return;

	UE_LOG(LogTemp, Warning, TEXT("PlayerController activo"));

	if (HealthWidgetClass)
	{
		HealthWidget = CreateWidget<UHealthWidget>(this, HealthWidgetClass);

		if (HealthWidget)
		{
			HealthWidget->AddToViewport();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No se pudo crear HealthWidget"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HealthWidgetClass es NULL"));
	}

	BindToCharacter();

	HealthModifier = Cast<AHealthModifier>(
	UGameplayStatics::GetActorOfClass(GetWorld(), AHealthModifier::StaticClass())
);
	if (HealthModifier)
	{
		UE_LOG(LogTemp, Warning, TEXT("HealthModifier encontrado"));
		HealthModifier->OnHealthTick.AddDynamic(this, &ACharacterPlayerController::HandleHealthTick);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No se encontro HealthModifier"));
	}

	if (IsLocalController())
	{
		ULocalPlayer* LocalPlayer = GetLocalPlayer();

		if (LocalPlayer)
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

			if (Subsystem && DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);

				UE_LOG(LogTemp, Warning, TEXT("MappingContext agregado"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Fallo al agregar MappingContext"));
			}
		}
	}
}

void ACharacterPlayerController::BindToCharacter()
{
	AEntregasPracticasCharacter* CharacterEntregasPracticas = Cast<AEntregasPracticasCharacter>(GetPawn());

	if (!CharacterEntregasPracticas)
	{
		UE_LOG(LogTemp, Error, TEXT("No se pudo obtener el Character"));
		return;
	}

	if (!CharacterEntregasPracticas->HealthComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Character no tiene HealthComponent"));
		return;
	}

	CharacterEntregasPracticas->HealthComponent->OnLifeChanged.AddDynamic(
		this,
		&ACharacterPlayerController::HandleLifeChanged
	);

	CharacterEntregasPracticas->HealthComponent->OnDeath.AddDynamic(this,
		&ACharacterPlayerController::HandleDeath
		);

	UE_LOG(LogTemp, Warning, TEXT("Bind a HealthComponent exitoso"));
}

void ACharacterPlayerController::HandleHealthTick(int32 TickCount)
{
	FString Message = FString::Printf(TEXT("Tick recibido: %d"), TickCount);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.0f,
			FColor::Green,
			Message
		);
	}

}

void ACharacterPlayerController::HandleLifeChanged(float CurrentHealth, float MaxHealth)
{
	if (HealthWidget)
	{
		HealthWidget->UpdateBar(CurrentHealth, MaxHealth);
	}
}

void ACharacterPlayerController::HandleDeath()
{
	UE_LOG(LogTemp, Error, TEXT("Personaje muerto"));
}
