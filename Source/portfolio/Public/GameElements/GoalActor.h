// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UWorld;

UCLASS()
class PORTFOLIO_API AGoalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Default")
	TSoftObjectPtr<UWorld> LoadLevel;

private:
	UPROPERTY(EditAnywhere,Category=Goal,meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> Goal;

	UPROPERTY(EditAnywhere, Category = Goal, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Sphere;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
