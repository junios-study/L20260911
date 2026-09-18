// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!IMC_Default.IsNull())
			{
				InputSystem->AddMappingContext(IMC_Default.LoadSynchronous(), 0);
			}

			//if (!IMC_Default)
			//{
			//	InputSystem->AddMappingContext(IMC_Default, 0);
			//}
		}
	}
}

