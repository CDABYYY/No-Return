// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Character.h"
#include "Y_GameInstance.h"
#include "Y.h"
#include "Y_StatusBar.h"
#include "Y_Floor.h"
#include "Y_UserWidget.h"
#include "Y_TimeLine.h"
#include "Y_BuffBar.h"
#include "Components/WidgetComponent.h"
#include "Y_ClassBase.h"

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

	BuffWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BuffWidgetComponent"));
	BuffWidget->SetupAttachment(RootComponent);
	static ConstructorHelpers::FClassFinder<UUserWidget>BuffWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UIBlueprints/BP_BuffBar.BP_BuffBar_C'"));
	BuffWidget->SetWidgetClass(BuffWidgetClass.Class);
	BuffWidget->SetRelativeLocation(FVector(0, 0, -100));
	BuffWidget->SetWidgetSpace(EWidgetSpace::Screen);
	BuffWidget->SetDrawSize(FVector2D(200, 80));

	

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
	ShowBuffs = new Y_StatusBar();
	//Buffs->AddBuff(new Y_Buff());
}

// Called when the game starts or when spawned
void AY_Character::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Call AddAtk"));
	Y::GetGameInstance()->AddAtk(this);
	if (UY_UserWidget* WidgetHealth = Cast<UY_UserWidget>(MyWidgetHealth->GetUserWidgetObject())) {
		WidgetHealth->UserWidgetInit(this);
	}
	if (UY_BuffBar* P = Cast<UY_BuffBar>(BuffWidget->GetUserWidgetObject()))
	{
		P->Owner = this;
		BuffBar = P;
		P->Update();
	}
}

// Called every frame
void AY_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);		
	float ToRotate = 90;
	if (Facing < 0) ToRotate *= -1;
	if (Rotating != ToRotate) {
		float RotateRate = 450;
		float DeltaRotate = RotateRate * DeltaTime;
		if (Facing < 0)DeltaRotate *= -1;
		if (ToRotate <= Rotating) {
			if (Rotating + DeltaRotate < ToRotate) {
				DeltaRotate = ToRotate - Rotating;
				Rotating = ToRotate;
			}
			else Rotating += DeltaRotate;
		}
		else {
			if (Rotating + DeltaRotate > ToRotate) {
				DeltaRotate = ToRotate - Rotating;
				Rotating = ToRotate;
			}
			else Rotating += DeltaRotate;
		}
		auto R = GetActorRotation();
		R.Yaw  = Rotating;
		SetActorRotation(R);
		//SetActorRelativeRotation(R);
		//AddActorLocalRotation(FRotator(0, DeltaRotate, 0));
		R = GetActorRotation();
	}
}

// Called to bind functionality to input
void AY_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AY_Character::AddBuff(TSharedPtr<class Y_Buff> Buff, bool Execute)
{
	if (Execute)Buffs->AddBuff(Buff);
	else ShowBuffs->AddBuff(Buff);
}

bool AY_Character::ChangeFacing(int32 ToChange)
{
	if (ToChange * Facing < 0) {
		Facing *= -1;
		return true;
	}
	return false;
}

int32 AY_Character::ExecuteAction(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs,int32 ExecuteCondition,FString TriggerAction, bool TryAttack)
{
	return Buffs->ExecuteBuffs(FromCharacter, ToCharacter, ToBuffs, ExecuteCondition, TriggerAction, TryAttack);
}

void AY_Character::CharacterMove(int32 Distance, bool Execute, FText Causer)
{
	Y_StatusBar S{ Y::YMakeShared<MoveBuff>(Distance) };
	Y::ExecuteAction(this,this, S, Causer.ToString(), Execute);
	int32 ToPos = StandFloor->SerialNumber + Distance;
	if (Execute && ToPos>=0 && ToPos < Y::GetFloors().Num() && IsValid(Y::GetFloors()[ToPos]) && !IsValid(Y::GetFloors()[ToPos]->StandCharacter)) {
		CharacterLogicalMove(Y::GetFloors()[ToPos]);
	}
}

void AY_Character::Update()
{
	if (IsValid(BuffBar))BuffBar->Update();
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
	if (StandFloor == TargetFloor)return;
	if (IsValid(StandFloor)) {
		StandFloor->Leave(this);
		int32 a = StandFloor->SerialNumber;
		int32 b = TargetFloor->SerialNumber;
		if (a > b)Swap(a, b);
		for (int32 i = a + 1; i < b; i++)
		{
			Y::GetFloors()[i]->Pass(this);
		}
		StandFloor->StandCharacter = nullptr;
	}
	TargetFloor->Enter(this);
	TargetFloor->StandCharacter = this;
	StandFloor = TargetFloor;
}

void AY_Character::AddBuffImmediately(TSharedPtr<class Y_Buff> AddedBuff)
{
	AddedBuff->AddToCharacter(this);
}

void AY_Character::ChangeAttackTime(int32 ChangedTime)
{
	UY_TimeLine::YTimeLine->RemoveCharacter(this);
	CharacterAttackTime = ChangedTime;
	UY_TimeLine::YTimeLine->AddCharacter(this);
}


