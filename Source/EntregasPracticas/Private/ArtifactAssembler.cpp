// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtifactAssembler.h"

#include "FragmentItem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AArtifactAssembler::AArtifactAssembler()
{
    PrimaryActorTick.bCanEverTick = false;
 
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
}

void AArtifactAssembler::Interact_Implementation(ACharacter* Character)
{
    if (!bReady || bAssembling) return;
 
    bAssembling = true;
    UE_LOG(LogTemp, Log, TEXT("[ArtifactAssembler] Ensamblado iniciado. Esperando %.1fs..."), AssembleDelay);
 
    GetWorldTimerManager().SetTimer(
        AssembleTimerHandle,
        this,
        &AArtifactAssembler::ExecuteAssemble,
        AssembleDelay,
        false
    );
}

void AArtifactAssembler::BeginPlay()
{
    Super::BeginPlay();
 
    Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
 
    TArray<AActor*> FoundItems;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFragmentItem::StaticClass(), FoundItems);
 
    TotalFragments = FoundItems.Num();
    UE_LOG(LogTemp, Log, TEXT("[ArtifactAssembler] FragmentItems en nivel: %d"), TotalFragments);
 
    for (AActor* Actor : FoundItems)
    {
        if (AFragmentItem* Item = Cast<AFragmentItem>(Actor))
        {
            Item->OnFragmentCollected.AddDynamic(this, &AArtifactAssembler::OnFragmentCollected);
        }
    }
 
    if (TotalFragments == 0)
    {
        SetReady();
    }
}
 
void AArtifactAssembler::OnFragmentCollected(FName FragmentID)
{
    CollectedFragments++;
    UE_LOG(LogTemp, Log, TEXT("[ArtifactAssembler] Fragmento '%s' recibido. %d / %d"),
        *FragmentID.ToString(), CollectedFragments, TotalFragments);
 
    CheckCompletion();
}
 
void AArtifactAssembler::CheckCompletion()
{
    if (!bReady && CollectedFragments >= TotalFragments)
    {
        UE_LOG(LogTemp, Log, TEXT("[ArtifactAssembler] Todos los fragmentos recolectados."));
        SetReady();
    }
}
 
void AArtifactAssembler::SetReady()
{
    bReady = true;
    Mesh->SetCollisionResponseToAllChannels(ECR_Block);
 
    if (ActiveMaterial)
    {
        Mesh->SetMaterial(0, ActiveMaterial);
    }
 
    UE_LOG(LogTemp, Log, TEXT("[ArtifactAssembler] Listo para interactuar."));
}
 

 
void AArtifactAssembler::ExecuteAssemble()
{
    if (!ActorToSpawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("[ArtifactAssembler] ActorToSpawn no asignado."));
        return;
    }
 
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
 
    AActor* Spawned = GetWorld()->SpawnActor<AActor>(
        ActorToSpawn,
        GetActorLocation() + SpawnOffset,
        FRotator::ZeroRotator,
        Params
    );
 
    if (Spawned)
    {
        UE_LOG(LogTemp, Log, TEXT("[ArtifactAssembler] Actor spawneado: %s"), *Spawned->GetName());
    }
 
    Destroy();
}
