// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPawn.h"

AMyGameModeBase::AMyGameModeBase()
{
	//CDO 골격 구조 기본값 설정

	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Hello World"));
	//}
	//UE_LOG(LogTemp, Warning, TEXT("Hello World"));

	//ClassName 저장 하고 싶어요. CDO 포인터를 쓰자.
	DefaultPawnClass = AMyPawn::StaticClass();
}
