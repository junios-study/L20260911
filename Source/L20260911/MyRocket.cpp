// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRocket.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyRocket::AMyRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	Movement->ProjectileGravityScale = 0;
	Movement->InitialSpeed = 2000.0f;
	Movement->MaxSpeed = 2000.f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/Rocket/Meshes/SM_Rocket.SM_Rocket'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	Body->SetRelativeRotation(FRotator(-90.f, 0, 0));
}

// Called when the game starts or when spawned
void AMyRocket::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AMyRocket::ProcessBeginOverlap);
	//OnActorBeginOverlap.RemoveDynamic(this, &AMyRocket::ProcessBeginOverlap);
	
	SetLifeSpan(3.0f);
}

// Called every frame
void AMyRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyRocket::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!OtherActor->ActorHasTag(TEXT("Player")))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplotionTemplate, GetActorLocation());

		UGameplayStatics::SpawnSoundAtLocation(GetWorld(),
			ExplotionSound, GetActorLocation());

		UGameplayStatics::ApplyDamage(OtherActor,
			10.0f,
			UGameplayStatics::GetPlayerController(GetWorld(), 0),
			this,
			nullptr
		);
		
		//CPP에서 점수 계산
		//점수 계산 기획자가 매번 바꿈.
		//CPP에서 호출 하지만 실행은 블루프린트에서 실행 되는 함수
		//CallCPPToExecuteBP();
		CallCPPToExecuteBPButDefaultCPP();

		UE_LOG(LogTemp, Warning, TEXT("Overlap"));
		Destroy();
	}
}


void AMyRocket::CallCPPToExecuteBPButDefaultCPP_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("이건 기본 CPP 동작"));
}

