// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_Trophy.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_Trophy : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Clicked();

	UFUNCTION(BlueprintCallable)
	void Init();

	void LoadInfo(TSharedPtr<class Y_TrophyInfo> LoadingInfo);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* UsingPicture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TrophyDescribe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TrophyAmount;

	TSharedPtr<class Y_TrophyInfo> Info;
};

class DEMO0_API Y_TrophyInfo 
{
public:
	virtual ~Y_TrophyInfo();
	int32 Counts;
	UTexture2D* UsingPicture;
	FText UsingDescibe;
	virtual UTexture2D* Picture();
	virtual FText Describe();
	virtual FText Amount();
	virtual void Clicked();
};

class DEMO0_API CardTrophy:public Y_TrophyInfo {
public:
	static TSharedPtr<CardTrophy> Share(std::initializer_list <TSharedPtr< class Y_CardInfo >> ToLoadInfos);
	static TSharedPtr<CardTrophy> Share();
	TArray<TSharedPtr<class Y_CardInfo>> CardInfos;
	CardTrophy(std::initializer_list <TSharedPtr< class Y_CardInfo >> ToLoadInfos);
	virtual void Clicked() override;
};

class DEMO0_API EquipmentTrophy :public Y_TrophyInfo {
public:
	TSharedPtr<class Y_Equipment> EquipmentInfo;
	static TSharedPtr<EquipmentTrophy> Share(TSharedPtr<class Y_Equipment> ToLoadInfo);
	static TSharedPtr<EquipmentTrophy> Share();
	EquipmentTrophy(TSharedPtr<class Y_Equipment> ToLoadInfo);
	virtual void Clicked() override;
};

class DEMO0_API MoneyTrophy :public Y_TrophyInfo {
public:
	int32 Money;
	static TSharedPtr<MoneyTrophy> Share(int32 MoneyCount);
	MoneyTrophy(int32 MoneyCount);
	virtual void Clicked() override;
};