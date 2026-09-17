// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStaticMeshComponent.h"

UMyStaticMeshComponent::UMyStaticMeshComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMyStaticMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("UMyStaticMeshComponent::TickComponent"));
	AddLocalRotation(FRotator(0, 0, RotationSpeed * DeltaTime));
}
