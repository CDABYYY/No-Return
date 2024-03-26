// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_PlayerController.h"
#include "Y_GameInstance.h"
#include "Y_HUD.h"

AY_PlayerController* AY_PlayerController::ThisPlayerController = nullptr;

void AY_PlayerController::BeginPlay()
{
	ThisPlayerController = this;
	/*static ConstructorHelpers::FClassFinder<UUserWidget>WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/BP_Y_HUD.BP_Y_HUD_C'"));
	MyHUD = CreateWidget<UUserWidget>(this, WidgetClass.Class);
	if (MyHUD)MyHUD->AddToViewport();
	else GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Failed"));*/
	UE_LOG(LogTemp, Warning, TEXT("Controller BeginPlay"));
	if (HUDAsset) {
		MyY_HUD = CreateWidget<UUserWidget>(this, HUDAsset);
	}
	if (MyHUD) {
		PCHUD = Cast<UY_HUD>(MyY_HUD);
		if (IsValid(PCHUD)) {
			PCHUD->YGameInstance = UY_GameInstance::YGI;
		}
		MyY_HUD->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("TimeLine Create"));
	}
	//else GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Failed"));
	//MyHUD->MarkPendingKill();
	//MyHUD->RemoveFromViewport();
	//MyHUD->RemoveFromParent();
}
