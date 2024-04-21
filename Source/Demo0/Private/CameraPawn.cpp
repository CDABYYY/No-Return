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
	
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		PlayerController->SetShowMouseCursor(true);
		if (UY_GameInstance* GI = Cast<UY_GameInstance>(GetGameInstance())) {
			GI->YC = this;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("GameInstance Connect Successfully!"));
		}
	}
	//Temp
	Y::GetController()->UpdateMap();
	Y::GetController()->MapWidget->PullMap(false);
	Y::GetController()->LoadHUD();
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + CurrentVelocity * DeltaTime);
	if(!ClickAble){
		Y::GetGameInstance()->HelpTick(DeltaTime);
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
					AActor* HitActor = HitResult.GetActor();
					if (AY_Card* HitCard = Cast<AY_Card>(HitActor)) {
						if (ChoosedCard != nullptr)ChoosedCard->SetColor("None");
						ChoosedCard = HitCard;
						HitCard->Clicked();
					}
					else if (AY_Floor* HitFloor = Cast<AY_Floor>(HitActor)) {
						Y::GetMainCharacter()->ChangeFacing(HitFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber);
						if (ChoosedFloor != nullptr)ChoosedFloor->SetColor("None");
						ChoosedFloor = HitFloor;
						HitFloor->Clicked();
						if (ChoosedCard != nullptr && ChoosedCard->AcceptFloor(ChoosedFloor)) {
							ChoosedCard->Play();
							if (!IsValid(Y::GetMainCharacter())) {
								return;
							}
							//ChoosedCard->SetColor(TEXT("None")); 

							Y::GetMainCharacter()->CharacterAttackTime += ChoosedCard->Info->CurrentCost;
							Y::GetMainCharacter()->ChangeAttackTime(Y::GetMainCharacter()->CharacterAttackTime);
							//Y::GetGameInstance()->AddAtk(Y::GetMainCharacter());

							Y::GetGameInfo()->UseCard(ChoosedCard);
							ChoosedCard = nullptr;
							for (auto& f : UY_GameInstance::YGI->Floors) {
								if (f != nullptr)f->SetColor(TEXT("None"));
							}
							
							ClickAble = false;
						}
					}
				}
			}
		}
	}
}

void ACameraPawn::MouseLeftRelease()
{
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

