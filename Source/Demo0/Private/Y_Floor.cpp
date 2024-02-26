// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Floor.h"
#include "Y_GameInstance.h"

// Sets default values
AY_Floor::AY_Floor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshComponentAsset(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/EditorCube.EditorCube'"));
	if (MeshComponent == NULL) {
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("CardMesh");
		MeshComponent->SetupAttachment(GetRootComponent());
		if (MeshComponentAsset.Succeeded()) {
			SetRootComponent(MeshComponent);
			MeshComponent->SetStaticMesh(MeshComponentAsset.Object);
			//MeshComponent->SetRelativeRotation(FRotator(0, 0, 0));
			MeshComponent->SetWorldScale3D(FVector(0.5));
		}
	}
}

// Called when the game starts or when spawned
void AY_Floor::BeginPlay()
{
	Super::BeginPlay();
	UY_GameInstance::YGI->Floors[SerialNumber] = this;
}

// Called every frame
void AY_Floor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AY_Floor::Clicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("Floor Clicked!"));
	SetColor(TEXT("Green"));
}

FVector AY_Floor::TargetLocation()
{
	
	return GetActorLocation() + FVector(0, 0, 64);//Half of Mesh Size
}

void AY_Floor::SetColor(FName MaterialName)
{
	if (UY_GameInstance* GI = Cast<UY_GameInstance>(GetGameInstance())) {
		GI->SetColor(MeshComponent, MaterialName);
	}
}

