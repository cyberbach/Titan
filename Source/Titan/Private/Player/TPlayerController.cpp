// Created by Andrey cb Mikheev

#include "Player/TPlayerController.h"

void ATPlayerController::OnPossess(APawn* newPawn)
{
	Super::OnPossess(newPawn);

	TPlayerCharacter = Cast<ATPlayerCharacter>(newPawn);
	if (TPlayerCharacter) {
		TPlayerCharacter->ServerSideInit();
	}
}

void ATPlayerController::AcknowledgePossession(APawn* newPawn)
{
	Super::AcknowledgePossession(newPawn);

	TPlayerCharacter = Cast<ATPlayerCharacter>(newPawn);
	if (TPlayerCharacter) {
		TPlayerCharacter->ClientSideInit();
	}
}

