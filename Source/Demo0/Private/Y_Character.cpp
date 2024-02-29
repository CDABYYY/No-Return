// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Character.h"
#include "Y_GameInstance.h"
#include "Y.h"
#include "Components/WidgetComponent.h"

// Sets default values
AY_Character::AY_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyWidgetHealth = CreateDefaultSubobject<UWidgetComponent>(TEXT("MyWidgetComponent"));
	MyWidgetHealth->SetupAttachment(RootComponent);
	static ConstructorHelpers::FClassFinder<UUserWidget>WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/BP_Y_UserWidget.BP_Y_UserWidget_C'"));
	MyWidgetHealth->SetWidgetClass(WidgetClass.Class);
	MyWidgetHealth->SetRelativeLocation(FVector(0, 0, 100));
	MyWidgetHealth->SetWidgetSpace(EWidgetSpace::Screen);
	MyWidgetHealth->SetDrawSize(FVector2D(200, 30));
	//MyWidgetHealth->SetRelativeRotation(FRotator(0, 90, 0));


	CharacterPriority=0;
	CharacterAttackTime=0;
	MaxHealth=100;
	Health=100;
	Shield=0;
	CharacterStatus = 0;

	StandFloor = nullptr;

}

// Called when the game starts or when spawned
void AY_Character::BeginPlay()
{
	Super::BeginPlay();
	Y::GetGameInstance()->AddAtk(this);
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

void AY_Character::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Character Attack!"));
}

void AY_Character::Injured()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Character Injured!"));
}


