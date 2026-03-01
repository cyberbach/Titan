// Created by Andrey cb Mikheev

#include "Player/TPlayerController.h"
#include "Widgets/GameplayWidget.h"

//////////////////////////////////////////////////////////////////////////
// On Possess

void ATPlayerController::OnPossess(APawn* newPawn)
{
	Super::OnPossess(newPawn);

	TPlayerCharacter = Cast<ATPlayerCharacter>(newPawn);
	if (TPlayerCharacter) {
		TPlayerCharacter->ServerSideInit();
	}
}

//////////////////////////////////////////////////////////////////////////
// Acknowledge Possession

void ATPlayerController::AcknowledgePossession(APawn* newPawn)
{
	Super::AcknowledgePossession(newPawn);

	TPlayerCharacter = Cast<ATPlayerCharacter>(newPawn);
	if (TPlayerCharacter) {
		TPlayerCharacter->ClientSideInit();
		SpawnGameplayWidget();
	}
}

//////////////////////////////////////////////////////////////////////////
// Spawn Gameplay Widget

void ATPlayerController::SpawnGameplayWidget()
{
	if (!IsLocalPlayerController() || !GameplayWidgetClass)
	{
		return;
	}

	GameplayWidget = CreateWidget<UGameplayWidget>(this, GameplayWidgetClass);
	if (GameplayWidget) {
		GameplayWidget->AddToViewport();
	}
}

