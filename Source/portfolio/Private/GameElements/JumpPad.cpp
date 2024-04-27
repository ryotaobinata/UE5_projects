// Fill out your copyright notice in the Description page of Project Settings.


#include "GameElements/JumpPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "portfolio/BallCharacter.h"

// Sets default values
AJumpPad::AJumpPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	JumpPadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = JumpPadMesh;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Box->SetupAttachment(RootComponent);
	Box->SetBoxExtent(FVector(50.f, 50.f, 10.f));
	Box->OnComponentBeginOverlap.AddDynamic(this, &AJumpPad::OnBoxBeginOverlap);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	Arrow->SetupAttachment(RootComponent);
	Arrow->bHiddenInGame=false;
	Arrow->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));


}

// Called when the game starts or when spawned
void AJumpPad::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJumpPad::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABallCharacter* Player=Cast<ABallCharacter>(OtherActor))
	{
		FVector Impulse = Arrow->GetForwardVector() * JumpImpulse;
		Player->Bound(Impulse);
	}
}

// Called every frame


