// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_PlayerController.h"
#include "Y_GameInstance.h"
#include "Y_HUD.h"

void AY_PlayerController::BeginPlay()
{
	/*static ConstructorHelpers::FClassFinder<UUserWidget>WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/BP_Y_HUD.BP_Y_HUD_C'"));
	MyHUD = CreateWidget<UUserWidget>(this, WidgetClass.Class);
	if (MyHUD)MyHUD->AddToViewport();
	else GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Failed"));*/
	if (HUDAsset) {
		MyHUD = CreateWidget<UUserWidget>(this, HUDAsset);
	}
	if (MyHUD) {
		if (UY_HUD* YHUD = Cast<UY_HUD>(MyHUD)) {
				YHUD->YGameInstance = UY_GameInstance::YGI;
		}
		MyHUD->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("TimeLine Create"));
	}
	//else GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Failed"));
	//MyHUD->MarkPendingKill();
	//MyHUD->RemoveFromViewport();
	//MyHUD->RemoveFromParent();
}
