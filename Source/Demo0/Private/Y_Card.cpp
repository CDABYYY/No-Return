// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Card.h"
#include "Components/BoxComponent.h"
#include "Y_GameInstance.h"
#include "Y_Character.h"
#include "Y_Floor.h"
#include "CameraPawn.h"
#include "Y.h"
#include "YCard01.h"
#include "Y_CardInfo.h"
#include "Y_Fighting.h"
#include "Kismet/KismetMaterialLibrary.h"

FName AY_Card::CardName = FName(TEXT("Card0"));

TMap<FName, TSubclassOf<AY_Card>>& AY_Card::CM = AY_Card::AddMap(TEXT("Card0"), AY_Card::StaticClass());

// Sets default values
AY_Card::AY_Card()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshComponentAsset(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshComponentAsset(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/EditorCube.EditorCube'"));
	if (MeshComponent == NULL) {
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("CardMesh");
		MeshComponent->SetupAttachment(GetRootComponent());
		if (MeshComponentAsset.Succeeded()) {
			MeshComponent->SetStaticMesh(MeshComponentAsset.Object);
			MeshComponent->SetRelativeLocation(FVector(0.f, 0, 0));
			//MeshComponent->SetRelativeRotation(FRotator(0, 0, 0));
			MeshComponent->SetWorldScale3D(FVector(0.01, 0.2, 0.32));
		}
	}
	SetRootComponent(MeshComponent);


	CardShapeInit(TEXT("/Script/Engine.Material'/Game/Resource/Png/JayceQ.JayceQ'"));
	NowCost = CardCost = 10;
	Info = MakeShared<Y_CardInfo>();
	Info->Owner = this;
}

// Called when the game starts or when spawned
void AY_Card::BeginPlay()
{
	Super::BeginPlay();
}

void AY_Card::CardShapeInit(const TCHAR* name)
{
	
	UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, name);
	UMaterialInstance* DynamicMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Material);
	/*static ConstructorHelpers::FObjectFinder<UMaterialInstance>MaterialObj(name);
	UMaterialInstance* DynamicMaterial = MaterialObj.Object;*/
	if (DynamicMaterial)
		MeshComponent->SetMaterial(0, DynamicMaterial);/*
	else 
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Can't Find Material"));*/

}

// Called every frame
void AY_Card::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector AF = Y::GetPlayer()->MyCamera->GetComponentLocation() + FVector(270, -52 * 4, -90);
	if (GetActorLocation() != AF + FVector(0, ToPosition, 0)) {
		float ToGo = DeltaTime * 200;
		if (NowPosition + ToGo < ToPosition)NowPosition += ToGo;
		else if (NowPosition - ToGo > ToPosition)NowPosition -= ToGo;
		else NowPosition = ToPosition;
		SetActorLocation(AF + FVector(0, NowPosition, 0));
	}
}

void AY_Card::Clicked()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Card Clicked!"));
	//SetColor(TEXT("Blue"));
	//for (auto&& f : UY_GameInstance::YGI->Floors) {
	//	if (f != nullptr && AcceptFloor(f))f->SetColor(TEXT("Yellow"));
	//}
	SetColor(TEXT("Blue"));
	Info->Clicked();
}

void AY_Card::Play()
{
	Info->Play(true);
	//UY_GameInstance::YGI->MainCharacter->MyPlayMontage(TEXT("Attack4"), UY_GameInstance::YGI->YC->ChoosedFloor, 1, true);
	//Y::GetMainCharacter()->CharacterLogicalMove(Y::GetPlayer()->ChoosedFloor);
	//DrawCard();
}

void AY_Card::Init()
{
	CardDescibe = Info->GetCardDescribe();
	CardCost = Info->GetCost();
	Picture = Info->GetPicture();
	CardID = Info->CardID;
	CardLabel = Info->GetName();
}

void AY_Card::SetColor(FName MaterialName)
{
	if (UY_GameInstance* GI = Cast<UY_GameInstance>(GetGameInstance())) {
		GI->SetColor(MeshComponent, MaterialName);
	}
}

bool AY_Card::AcceptFloor(AY_Floor* TargetFloor)
{
	//AY_Floor* nowFloor = UY_GameInstance::YGI->MainCharacter->StandFloor;
	//if (TargetFloor != nullptr) {
	//	return TargetFloor->SerialNumber <= nowFloor->SerialNumber + 3 && TargetFloor->SerialNumber >= nowFloor->SerialNumber - 3;
	//}
	//return false;
	return Info->AcceptFloor(TargetFloor);
}

void AY_Card::UseCard(AY_Card* UsedCard)
{
	Y::GetGameInfo()->UseCard(UsedCard);
}

void AY_Card::DrawCard(TSharedPtr<class Y_CardInfo> ToDrawCard, bool VoidSpawn)
{
	Y::GetGameInfo()->DrawCard(ToDrawCard, VoidSpawn);
}

void AY_Card::DrawCard(int32 DrawCount)
{
	Y::GetGameInfo()->DrawCard(DrawCount);
}


TMap<FName, TSubclassOf<AY_Card>>& AY_Card::AddMap(FName AddCardName, TSubclassOf<AY_Card> AddCardClass)
{
	static TMap<FName, TSubclassOf<AY_Card>> Map;
	if (AddCardName != FName() && !Map.Contains(AddCardName)) {
		Map.Add(AddCardName, AddCardClass);
	}
	return Map;
}

