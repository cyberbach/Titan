// Created by Andrey cb Mikheev

#include "Character/TCharacter.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Widgets/OverHeadStatsGauge.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// ATCharacter

ATCharacter::ATCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TAbilitySystemComponent = CreateDefaultSubobject<UTAbilitySystemComponent>(TEXT("T Ability System Component"));
	TAttributeSet = CreateDefaultSubobject<UTAttributeSet>(TEXT("T Attribute Set"));

	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Over Head Widget Component"));
	OverHeadWidgetComponent->SetupAttachment(GetRootComponent());
}

//////////////////////////////////////////////////////////////////////////
// Server Side Init

void ATCharacter::ServerSideInit()
{
	TAbilitySystemComponent->InitAbilityActorInfo(this, this);
	TAbilitySystemComponent->ApplyInitialEffects();
	TAbilitySystemComponent->GiveInitialAbilities();
}

//////////////////////////////////////////////////////////////////////////
// Client Side Init

void ATCharacter::ClientSideInit()
{
	TAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

//////////////////////////////////////////////////////////////////////////
// Is Locally Controlled By Player

bool ATCharacter::IsLocallyControlledByPlayer() const
{
	return GetController() && GetController()->IsPlayerController() && GetController()->IsLocalController();
}

//////////////////////////////////////////////////////////////////////////
// Possessed By

void ATCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (NewController && !NewController->IsPlayerController()) {
		// Bots and NPCs should run server-side init on the server, but not client-side init on the owning client
		ServerSideInit();
	}	
}

//////////////////////////////////////////////////////////////////////////
// Begin Play

void ATCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	ConfigureOverHeadStatusWidget();
}

//////////////////////////////////////////////////////////////////////////
// Tick

void ATCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//////////////////////////////////////////////////////////////////////////
// Setup Player Input Component

void ATCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//////////////////////////////////////////////////////////////////////////
// Configure Over Head Status Widget

void ATCharacter::ConfigureOverHeadStatusWidget()
{
	if(IsLocallyControlledByPlayer() || !OverHeadWidgetComponent)
	{
		// Don't show overhead widget for local player or if the component is not valid
		OverHeadWidgetComponent->SetVisibility(false);
		OverHeadWidgetComponent->SetHiddenInGame(true);
		return;
	}

	UOverHeadStatsGauge* OverHeadStatsGauge = Cast<UOverHeadStatsGauge>(OverHeadWidgetComponent->GetUserWidgetObject());
	if(OverHeadStatsGauge)
	{
		// Configure the overhead widget with the character's ability system component to display relevant stats
		OverHeadStatsGauge->ConfigureWithASC(TAbilitySystemComponent);
		OverHeadWidgetComponent->SetVisibility(true);
		OverHeadWidgetComponent->SetHiddenInGame(false);

		GetWorldTimerManager().ClearTimer(OverHeadWidgetVisibilityUpdateTimerHandle);
		GetWorldTimerManager().SetTimer(OverHeadWidgetVisibilityUpdateTimerHandle, this, &ATCharacter::UpdateOverHeadWidgetVisibility, OverHeadWidgetVisibilityUpdateInterval, true);
	}	
}

//////////////////////////////////////////////////////////////////////////
// Update Over Head Widget Visibility

void ATCharacter::UpdateOverHeadWidgetVisibility()
{
	APawn* LocalPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if(LocalPawn)
	{
		float DistanceSquaredToLocalPawn = FVector::DistSquared(GetActorLocation(), LocalPawn->GetActorLocation());
		bool bShouldBeVisible = DistanceSquaredToLocalPawn <= OverHeadWidgetVisibilityDistance;
		OverHeadWidgetComponent->SetVisibility(bShouldBeVisible);
		OverHeadWidgetComponent->SetHiddenInGame(!bShouldBeVisible);
	}
}

