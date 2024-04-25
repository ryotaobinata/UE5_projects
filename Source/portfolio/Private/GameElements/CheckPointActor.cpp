// Fill out your copyright notice in the Description page of Project Settings.


#include "GameElements/CheckPointActor.h"
#include "Components/SphereComponent.h"
#include "portfolio/BallCharacter.h"
#include "portfolio/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACheckPointActor::ACheckPointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	Checkpoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponentCheckPoint"));
	RootComponent = Checkpoint;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(RootComponent);
	Sphere->SetSphereRadius(70.f);

	CheckTransform = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	CheckTransform->SetupAttachment(RootComponent);
	CheckTransform->SetRelativeLocation(FVector(0.f, 0.f, 100.f));

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACheckPointActor::OnSphereBeginOverlap);

}

// Called when the game starts or when spawned
void ACheckPointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame


void ACheckPointActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//接触したアクタ―がプレイヤーか判定
	if (const ABallCharacter* Player=Cast<ABallCharacter>(OtherActor))
	{
		//gamemodeを取得してキャスト
		if (AMyGameModeBase* Gamemode=Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			//チェックポイントのワールドトランスフォームを取得
			const FTransform& WorldTransform = CheckTransform->GetComponentToWorld();
			
			//現在のリスポーン位置が異なれば更新
			if (!Gamemode->SpawnTransform.Equals(WorldTransform))
			{
				Gamemode->SpawnTransform = WorldTransform;
			}
		}
	}
}

