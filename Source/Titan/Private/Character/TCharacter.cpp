// Created by Andrey cb Mikheev


#include "Character/TCharacter.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ATCharacter::ATCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ATCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

