// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UArrowComponent;

UCLASS()
class PORTFOLIO_API AJumpPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = JumpPad, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent>JumpPadMesh;

	UPROPERTY(VisibleAnywhere, Category = JumpPad, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, Category = JumpPad, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> Arrow;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	float JumpImpulse=1000.f;

};
