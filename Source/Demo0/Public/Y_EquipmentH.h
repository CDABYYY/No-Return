// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_EquipmentH.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_EquipmentH : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void Update();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UY_EquipmentW* >Equipments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UY_EquipmentW* ChoosedEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Pressing;

	UFUNCTION(BlueprintCallable)
	void RemoveEquipment(class UY_EquipmentW* ToRemoveEquipment);

	UFUNCTION(BlueprintCallable)
	void Clear();

	void AddEquipment(TSharedPtr<class Y_Equipment> Equipment);

	UFUNCTION(BlueprintImplementableEvent)
	class UY_EquipmentW* CreateEquipment();
};
