// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPointActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class PORTFOLIO_API ACheckPointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckPointActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Checkpoint;

	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> CheckTransform;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
