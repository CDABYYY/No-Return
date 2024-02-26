// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Card.h"
#include "Components/BoxComponent.h"
#include "Y_GameInstance.h"
#include "Y_Character.h"
#include "Y_Floor.h"
#include "Kismet/KismetMaterialLibrary.h"

// Sets default values
AY_Card::AY_Card()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CardShapeInit(TEXT("/Script/Engine.Material'/Game/Resource/Png/JayceW.JayceW'"));
	SetRootComponent(MeshComponent);
}

// Called when the game starts or when spawned
void AY_Card::BeginPlay()
{
	Super::BeginPlay();
}

void AY_Card::CardShapeInit(const TCHAR* name)
{
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshComponentAsset(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshComponentAsset(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/EditorCube.EditorCube'"));
	if (MeshComponent == NULL) {
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("CardMesh");
		MeshComponent->SetupAttachment(GetRootComponent());
		if (MeshComponentAsset.Succeeded()) {
			MeshComponent->SetStaticMesh(MeshComponentAsset.Object);
			MeshComponent->SetRelativeLocation(FVector(0.f, 0, 0));
			//MeshComponent->SetRelativeRotation(FRotator(0, 0, 0));
			MeshComponent->SetWorldScale3D(FVector(0.01,0.2,0.32));
		}
	}
	UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, name);
	UMaterialInstance* DynamicMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Material);
	/*static ConstructorHelpers::FObjectFinder<UMaterialInstance>MaterialObj(name);
	UMaterialInstance* DynamicMaterial = MaterialObj.Object;*/
	if (DynamicMaterial)
		MeshComponent->SetMaterial(0, DynamicMaterial);
	else GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Can't Find Material"));
}

// Called every frame
void AY_Card::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AY_Card::Clicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Card Clicked!"));
	SetColor(TEXT("Blue"));
	for (int32 i = -1; i <= 1; i++)
	{
		int32 i0 = i + UY_GameInstance::YGI->MainCharacter->StandFloor;
		if (i0 >= 0 && i0 < 20 && UY_GameInstance::YGI->Floors[i0] != nullptr) {
			UY_GameInstance::YGI->Floors[i0]->SetColor(TEXT("Yellow"));
		}
	}
}

void AY_Card::SetColor(FName MaterialName)
{
	if (UY_GameInstance* GI = Cast<UY_GameInstance>(GetGameInstance())) {
		GI->SetColor(MeshComponent, MaterialName);
	}
}

