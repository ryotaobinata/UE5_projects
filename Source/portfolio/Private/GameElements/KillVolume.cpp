// Fill out your copyright notice in the Description page of Project Settings.


#include "GameElements/KillVolume.h"
#include "Components/BoxComponent.h"
#include "Framework/MyGameModeBase.h"
#include "portfolio/BallCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AKillVolume::AKillVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = DefaultSceneRoot;

	KillVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	KillVolume->SetupAttachment(RootComponent);
	KillVolume->OnComponentBeginOverlap.AddDynamic(this, &AKillVolume::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void AKillVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKillVolume::OnConstruction(const FTransform& Transform)
{
	KillVolume->SetBoxExtent(BoxExtent);
}

// Called every frame
void AKillVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillVolume::OnBoxBeginOverlap(UPrimitiveComponent* OvrlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABallCharacter* Player = Cast<ABallCharacter>(OtherActor)) {
		if (AMyGameModeBase* GameMode=Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			GameMode->KillPlayer(Player);
		}
	}
}

