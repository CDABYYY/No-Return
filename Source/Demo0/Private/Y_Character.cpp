// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Character.h"
#include "Y_GameInstance.h"
#include "Y.h"
#include "Y_StatusBar.h"
#include "Y_Floor.h"
#include "Y_UserWidget.h"
#include "Y_TimeLine.h"
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
	MyWidgetHealth->SetRelativeLocation(FVector(0, 0, 150));
	MyWidgetHealth->SetWidgetSpace(EWidgetSpace::Screen);
	MyWidgetHealth->SetDrawSize(FVector2D(200, 30));

	//MyWidgetHealth->SetRelativeRotation(FRotator(0, 90, 0));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	CharacterPriority=0;
	CharacterAttackTime=0;
	MaxHealth=20;
	Health=20;
	Shield=0;
	CharacterStatus = 0;

	StandFloor = nullptr;

	Buffs = new Y_StatusBar();
	Buffs->AddBuff(new Y_Buff());
}

// Called when the game starts or when spawned
void AY_Character::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Call AddAtk"));
	Y::GetGameInstance()->AddAtk(this);
	if (UY_UserWidget* WidgetHealth = Cast<UY_UserWidget>(MyWidgetHealth->GetUserWidgetObject())) {
		UE_LOG(LogTemp, Warning, TEXT("Widget Init"));
		WidgetHealth->UserWidgetInit(this);
	}
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


int32 AY_Character::ExecuteAction(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs,int32 ExecuteCondition,FString TriggerAction, bool TryAttack)
{
	return Buffs->ExecuteBuffs(FromCharacter, ToCharacter, ToBuffs, ExecuteCondition, TriggerAction, TryAttack);
}

void AY_Character::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Character Attack!"));
}

void AY_Character::CharacterDead()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Character Dead!"));
}

void AY_Character::CharacterLogicalMove(AY_Floor* TargetFloor)
{
	if (IsValid(StandFloor)) {
		StandFloor->StandCharacter = nullptr;
	}
	TargetFloor->StandCharacter = this;
	StandFloor = TargetFloor;
}

void AY_Character::ChangeAttackTime(int32 ChangedTime)
{
	UY_TimeLine::YTimeLine->RemoveCharacter(this);
	CharacterAttackTime = ChangedTime;
	UY_TimeLine::YTimeLine->AddCharacter(this);
}


