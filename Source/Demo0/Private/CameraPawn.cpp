// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Y_GameInstance.h"
#include "Y_Card.h"
#include "Y_Floor.h"
#include "Y_Character.h"
#include "Y.h"
#include "Y_PlayerController.h"
#include "Y_MapWidget.h"
#include "Y_CardInfo.h"
#include "Y_Fighting.h"
#include "Y_CardH.h"
#include "Y_Settle.h"
#include "Y_Trophy.h"
#include "Y_ChooseCard.h"
#include "Y_RoomWidget.h"
#include "Y_Equipment.h"
#include "Engine/LocalPlayer.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArmComponent"));
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCameraComponent"));
	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMeshComponent"));
	MySpringArm->TargetArmLength = 400.0f;
	CardSpawnStart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CardSpawnStart"));
	CardSpawnStart->SetRelativeLocation(FVector(250, 0, -90));
	

	/*static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshComponentAsset(TEXT("/ Script / Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (MeshComponentAsset.Succeeded()) {
		MyStaticMesh->SetStaticMesh(MeshComponentAsset.Object);
		MyStaticMesh->SetRelativeLocation(FVector(0.f, 0, -50));
	}*/

	SetRootComponent(MyStaticMesh);
	MySpringArm->SetupAttachment(RootComponent);
	MyCamera->SetupAttachment(MySpringArm);
	CardSpawnStart->SetupAttachment(MyCamera);
	//防止控制器转动影响角色转动
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	//使用pawn的旋转
	MySpringArm->bUsePawnControlRotation = true;

	MaxSpeed = 400.f;
	AutoPossessPlayer = EAutoReceiveInput::Player0;


	ChoosedCard = nullptr;
	ChoosedFloor = nullptr;
	ClickAble = true;
	FindingObject = false;
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		PlayerController->SetShowMouseCursor(true);
		if (UY_GameInstance* GI = Cast<UY_GameInstance>(GetGameInstance())) {
			GI->YC = this;
			AY_PlayerController::ThisPlayerController = Cast<AY_PlayerController>(PlayerController);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("GameInstance Connect Successfully!"));
		}
	}
	//Temp
	//Y::GetController()->UpdateMap();
	//Y::GetController()->MapWidget->PullMap(false);
	//Y::GetController()->LoadHUD();
	//Y::GetController()->ShowCards(false);
	//LookingTime = 0;
	//LookingFloor = nullptr;
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Y::GetGameInstance()->GameStatus == 1){
		SetActorLocation(GetActorLocation() + CurrentVelocity * DeltaTime);
		if (!ClickAble) {
			Y::GetGameInstance()->HelpTick(DeltaTime);
		}
		if (Y::IsPressingCard() || Y::IsPressingEquipment()) {
			FVector MouseLocation, MouseRotation, EndLocation;
			FHitResult HitResult;
			if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
				if (PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseRotation))
				{
					EndLocation = MouseLocation + MouseRotation * 10000;
					bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, MouseLocation, EndLocation, ECC_Visibility);
					if (bHit) {
						AActor* HitActor = HitResult.GetActor();
						AY_Floor* HitFloor = Cast<AY_Floor>(HitActor);
						if (!IsValid(HitFloor)) {
							AY_Character* HitCharacter = Cast<AY_Character>(HitActor);
							if (IsValid(HitCharacter))HitFloor = HitCharacter->StandFloor;
						}
						if (IsValid(HitFloor)) {
							Y::GetMainCharacter()->ChangeFacing(HitFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber);
							if (LookingFloor != HitFloor) {
								if (IsValid(LookingFloor)) {
									if (Y::IsPressingCard() && Y::GetChoosingCard()->AcceptFloor(LookingFloor) || Y::IsPressingEquipment() && Y::GetChoosingEquipment()->AcceptFloor(LookingFloor))
										LookingFloor->SetColor("Yellow");
									else LookingFloor->SetColor("None");
								}
								LookingFloor = HitFloor;
								ChoosedFloor = HitFloor;
								LookingTime = 0;
								for (auto& p : Y::GetEnemys())p->ShowToExecute(false);
								Y::GetMainCharacter()->ShowToExecute(false);
							}
							else {
								if (LookingTime < 0.5 && LookingTime + DeltaTime >= 0.5) {
									LookingFloor->SetColor(TEXT("Blue"));
									if (Y::IsPressingCard() && Y::GetChoosingCard().IsValid())
									{
										Y_StatusBar BA{ MakeShared<CardBuff>(Y::GetChoosingCard()) };
										if (Y::GetMainCharacter()->ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), BA, Y_Buff::BeginAction, Y::GetChoosingCard()->GetName().ToString(), false) == 0)
										{
											Y::GetChoosingCard()->CurrentCost = BA.Buff[0]->BuffCount;
											Y::GetChoosingCard()->Play(false);

											Y_StatusBar AA{ MakeShared<CardBuff>(Y::GetChoosingCard()) };
											Y::GetMainCharacter()->ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), AA, Y_Buff::AfterAction, Y::GetChoosingCard()->GetName().ToString(), false);
										}
									}
									else if (Y::IsPressingEquipment() && Y::GetChoosingEquipment().IsValid()) {
										Y::GetChoosingEquipment()->Play(false);
									}

									for (auto& p : Y::GetEnemys())p->ShowToExecute(true);
									Y::GetMainCharacter()->ShowToExecute(true);
								}
								LookingTime += DeltaTime;
							}
						}
					}
				}
			}
		}
	}
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACameraPawn::MoveRight);
	/*if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACameraPawn::Move);
	}*/
}

void ACameraPawn::MoveRight(float Value)
{
	CurrentVelocity.Y = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
}

void ACameraPawn::MouseLeftPress()
{
	if(ClickAble){
		FVector MouseLocation, MouseRotation, EndLocation;
		FHitResult HitResult;
		if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
			if (PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseRotation))
			{
				EndLocation = MouseLocation + MouseRotation * 10000;
				bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, MouseLocation, EndLocation, ECC_Visibility);
				if (bHit) {
					
					
				}
			}
		}
	}
}

void ACameraPawn::MouseLeftRelease()
{
	LookingFloor = nullptr;
	LookingTime = 0;
	if(Y::GetGameInstance()->GameStatus == 1)
	{
		if (Y::IsPressingCard() || Y::IsPressingEquipment()) {
			if (ClickAble) {
				FVector MouseLocation, MouseRotation, EndLocation;
				FHitResult HitResult;
				if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
					if (PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseRotation))
					{
						EndLocation = MouseLocation + MouseRotation * 10000;
						bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, MouseLocation, EndLocation, ECC_Visibility);
						if (bHit) {
							AActor* HitActor = HitResult.GetActor();
							AY_Floor* HitFloor = Cast<AY_Floor>(HitActor);
							if (!IsValid(HitFloor)) {
								AY_Character* HitCharacter = Cast<AY_Character>(HitActor);
								if (IsValid(HitCharacter))HitFloor = HitCharacter->StandFloor;
							}
							if (IsValid(HitFloor)) {
								Y::GetMainCharacter()->ChangeFacing(HitFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber);
								if (ChoosedFloor != nullptr)ChoosedFloor->SetColor("None");
								ChoosedFloor = HitFloor;
								HitFloor->Clicked();
								if (Y::IsPressingCard() && Y::GetChoosingCard().IsValid()) {
									if (Y::GetChoosingCard()->AcceptFloor(ChoosedFloor))
									{
										Y_StatusBar BA{ MakeShared<CardBuff>(Y::GetChoosingCard()) };
										if (Y::GetMainCharacter()->ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), BA, Y_Buff::BeginAction, Y::GetChoosingCard()->GetName().ToString(), true) == 0)
										{

											Y::GetGameInfo()->UseCard(Y::GetChoosingCard());
											Y::Log(0, TEXT("Execute Successfully"));

											int32 I = BA.Buff[0]->BuffCount;

											Y::GetChoosingCard()->CurrentCost = I;

											Y::GetChoosingCard()->Play(true);

											Y_StatusBar AA{ MakeShared<CardBuff>(Y::GetChoosingCard()) };
											Y::GetMainCharacter()->ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), AA, Y_Buff::AfterAction, Y::GetChoosingCard()->GetName().ToString(), true);
										}
										else {

											Y::GetGameInfo()->UseCard(Y::GetChoosingCard());
											Y::GetChoosingCard()->CurrentCost = BA.Buff[0]->BuffCount;
										}


										Y::GetMainCharacter()->CharacterAttackTime += Y::GetChoosingCard()->CurrentCost;
										Y::GetMainCharacter()->ChangeAttackTime(Y::GetMainCharacter()->CharacterAttackTime);

										Y::GetController()->CardWidget->RemoveCard(Y::GetChoosingCard()->OwnerWidget);

										ClickAble = false;
									}
									Y::GetController()->CardWidget->ChoosedCard = nullptr;
									Y::IsPressingCard() = false;
									Y::GetController()->CardWidget->Update();
									Y::GetController()->ShowCards(false);
								}
								else if (Y::IsPressingEquipment() && Y::GetChoosingEquipment().IsValid()) {
									Y::GetChoosingEquipment()->Play(true);
								}
							}
						}
					}
				}
			}
			for (auto& p : Y::GetFloors())if (IsValid(p))p->SetColor(TEXT("None"));

			for (auto& p : Y::GetEnemys())p->ShowToExecute(false);
			Y::GetMainCharacter()->ShowToExecute(false);
		}
	}
}

void ACameraPawn::TryExperimentFunction()
{
	//auto ChoosePtr = MakeShared<Y_ChooseCardInfo>();
	//ChoosePtr->Cards.Add(Y::CardClass[1]->NewObject());
	//ChoosePtr->Cards.Add(Y::CardClass[1]->NewObject());
	//ChoosePtr->Cards.Add(Y::CardClass[1]->NewObject());
	//Y::GetController()->BeginChoose(ChoosePtr);
	Y::GetGameInfo()->SettleInfo->TrophyInfos.Add(CardTrophy::Share({ Y::CardClass[1]->NewObject(), Y::CardClass[1]->NewObject(), Y::CardClass[1]->NewObject(), Y::CardClass[1]->NewObject() }));
	Y::GetController()->MapWidget->CurrentRoom->RoomClosed();
}

//void ACameraPawn::Move(const FInputActionValue& Value)
//{
//	float MovementFloat = Value.Get<float>();
//	if (Controller != nullptr) {
//		AddMovementInput(GetActorRightVector(), 100);
//		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("My Name is ok"));
//		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("%f"), MovementFloat);
//	}
//}

