// Fill out your copyright notice in the Description page of Project Settings.


#include "BallCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyGameModeBase.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"

// Sets default values
ABallCharacter::ABallCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = CharacterMesh;

	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Sphere"));
	CharacterMesh->SetStaticMesh(Mesh);
	UMaterial* Material = LoadObject<UMaterial>(nullptr, TEXT("/Engine/BasicShapes/BasicShapeMaterial"));
	CharacterMesh->SetMaterial(0,Material);

	CharacterMesh->SetSimulatePhysics(true);

	CharacterMesh->SetCollisionProfileName(TEXT("PhysicsActor"));

	CharacterMesh->BodyInstance.bNotifyRigidBodyCollision = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);

	//SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 400.f;

	//SpringArm->bInheritPitch = false;
	//SpringArm->bInheritRoll = false;
	//SpringArm->bInheritYaw = false;

	SpringArm->bEnableCameraLag = true;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	Arrow->SetupAttachment(Camera);
	Arrow->SetRelativeLocation(FVector(400.f, 0.f, 130.f));
	Arrow->bHiddenInGame=false;


	DefaultMappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/MappingContext/IM_Controls"));

	ControlAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/InputAction/IA_Controls"));

	LookAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/InputAction/IA_Look"));

	JumpAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/InputAction/IA_Jump"));

}

// Called when the game starts or when spawned
void ABallCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerContoroller=Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerContoroller->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

void ABallCharacter::ControlBall(const FInputActionValue& Value)
{
	const FVector2D V = Value.Get<FVector2D>();
	FVector ForceVector = FVector(V.Y, V.X, 0.0f)*Speed;
	FVector ArrowForceVector = Arrow->GetComponentToWorld().TransformVectorNoScale(ForceVector);
	CharacterMesh->AddForce(ArrowForceVector, TEXT("NONE"), true);
}

void ABallCharacter::Look(const FInputActionValue& Value)
{
	FVector2D v = Value.Get<FVector2D>();

	if (Controller!=nullptr)
	{
		AddControllerYawInput(v.X);
		AddControllerPitchInput(v.Y);

		FRotator controlRotate = GetControlRotation();

		double LimitPitchAngle = FMath::ClampAngle(controlRotate.Pitch, -40.f, -10.f);

		UGameplayStatics::GetPlayerController(this, 0)->SetControlRotation(FRotator(LimitPitchAngle,controlRotate.Yaw,0.f));
	}
}

void ABallCharacter::Jump(const FInputActionValue& Value)
{
	if (const bool V=Value.Get<bool>()&&CanJump)
	{
		CharacterMesh->AddImpulse(FVector(0.f, 0.f, JumpInpulse), TEXT("None"), true);
		CanJump = false;
	}
}

void ABallCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalInpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalInpulse, Hit);
	CanJump = true;
}

// Called every frame
/*
void ABallCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

// Called to bind functionality to input
void ABallCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ControlAction, ETriggerEvent::Triggered, this, &ABallCharacter::ControlBall);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABallCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABallCharacter::Jump);
	}

}



