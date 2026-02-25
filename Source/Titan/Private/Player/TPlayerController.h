// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player/TPlayerCharacter.h"
#include "GameFramework/Pawn.h"
#include "TPlayerController.generated.h"

//////////////////////////////////////////////////////////////////////////
// T Player Controller

UCLASS()
class ATPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Called when the controller possesses a new pawn. This will only run on the server.
	void OnPossess(APawn* newPawn) override;

	// Called when the client acknowledges possession of a new pawn.
	// This will only run on the client and listening server.
	// This is used to trigger client-side initialization of the pawn
	// after the server has possessed it.
	void AcknowledgePossession(APawn* newPawn) override;

private:
	UPROPERTY()
	ATPlayerCharacter* TPlayerCharacter;
};
