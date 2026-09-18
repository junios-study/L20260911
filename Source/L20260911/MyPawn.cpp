// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyStaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyRocket.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);


	//특별한 경우 아님 안함 절대로.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}


	Left = CreateDefaultSubobject<UMyStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);

	Right = CreateDefaultSubobject<UMyStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	Left->SetRelativeLocation(FVector(36.8f, -21.f, 1.3f));
	Right->SetRelativeLocation(FVector(36.8f, 21.f, 1.3f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	SpringArm->TargetArmLength = 120.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	Movement->MaxSpeed = 0.0f;

	Tags.Add(TEXT("Player"));

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector());
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);

	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPawn::Roll);

}

void AMyPawn::Pitch(float Value)
{
	AddActorLocalRotation(FRotator(FMath::Clamp(Value, -1, 1) * 60.0f * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		0,
		0)
	);
}

void AMyPawn::Roll(float Value)
{
	AddActorLocalRotation(FRotator(0,
		0,
		FMath::Clamp(Value, -1, 1) * 60.0f * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()))
	);
}

void AMyPawn::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("발사"));
	//문법적으로 CDO 가르키는 포인터
	//의미적으론 그냥 클래스 이름(C++ 문법이 없음)
	GetWorld()->SpawnActor<AActor>(AMyRocket::StaticClass(), 
		Arrow->K2_GetComponentToWorld());
}
