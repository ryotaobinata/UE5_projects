// Fill out your copyright notice in the Description page of Project Settings.


#include "GameElements/GoalActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "portfolio/BallCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoalActor::AGoalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	Goal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = Goal;

	//UStaticMesh* Mesh=LoadObject<UStaticMesh>(nullptr,TEXT(""));

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(RootComponent);

	Sphere->SetSphereRadius(72.f);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGoalActor::OnSphereBeginOverlap);
}

// Called when the game starts or when spawned
void AGoalActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void AGoalActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void AGoalActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const ABallCharacter* Character=Cast<ABallCharacter>(OtherActor))
	{
		//UE_LOG(LogTemp, Display, TEXT("Goal!!"));
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), this->LoadLevel);
	}
}

