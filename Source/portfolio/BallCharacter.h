// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "BallCharacter.generated.h"



class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UArrowComponent;

UCLASS()
class PORTFOLIO_API ABallCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABallCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ControlBall(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalInpulse, const FHitResult& Hit) override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Bound(const FVector boundpower);
	
private:
	UPROPERTY(EditAnywhere, Category = Character,meta=(AllowPrivateAccses="true"))
	TObjectPtr<UStaticMeshComponent> CharacterMesh;
	//UStaticMeshComponent* CharacterMesh;
	UPROPERTY(EditAnywhere, Category = Camera, meta=(AllowPrivateAccses = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;
	//USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, Category = Camera, meta=(AllowPrivateAccses = "true"))
	TObjectPtr<UCameraComponent> Camera;
	//UCameraComponent* Camera;

	UPROPERTY(EditAnywhere,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ControlAction;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Control, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> Arrow;

	float Speed=300.0f;

	float JumpInpulse = 500.f;
	bool CanJump = false;
};
