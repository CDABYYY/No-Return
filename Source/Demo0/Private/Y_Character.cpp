// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Character.h"
#include "Y_GameInstance.h"

// Sets default values
AY_Character::AY_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AY_Character::BeginPlay()
{
	Super::BeginPlay();
	UY_GameInstance::MainCharacter = this;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Character"));
}

// Called every frame
void AY_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AY_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

