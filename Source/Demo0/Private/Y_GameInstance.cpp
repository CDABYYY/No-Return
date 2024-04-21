// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_GameInstance.h"
#include "Y_Ally.h"
#include "CameraPawn.h"
#include "Y_Card.h"
#include "Y_Floor.h"
#include "Y_TimeLine.h"
#include "Y.h"
#include "Y_Enemy.h"
#include "Y_RoomWidget.h"
#include "Y_Fighting.h"
#include "Y_CardInfo.h"
#include "Y_EnemyInfo.h"

#include "Y_ClassBase.h"


#include "IImageWrapper.h"
#include "IImageWrapperModule.h"

UY_GameInstance* UY_GameInstance::YGI = nullptr;



UY_GameInstance::UY_GameInstance()
{
	RunTime = 0;
	YGI = this;
	Cards.SetNum(0);
	//For Debug StartMap
	Floors.SetNum(0);
	AtkOrder.SetNum(0);

	NowVector = FVector(0,0,300);
	NowRotator = FRotator(0,0,0);

	//RandomStream = FRandomStream(0);
	HaveRandoms = 0;

	FightInfo = MakeShared<Y_Fighting>();


	Y::LoadBuff<Y_Buff>(0);
	Y::LoadCard<Y_CardInfo>(0);
	Y::LoadCharacter<Y_EnemyInfo>(0);
	Y::LoadFloor<Y_FloorInfo>(0);
	Y::LoadRoom<Y_RoomInfo>(0);

	LoadY_Base();

	//TEMP
	FightInfo->ReadyRooms.Add(Y::RoomClass[1]->NewObject());

	//TEMP
	for(int i = 0;i<10;i++)
	FightInfo->UsingCards.Add(Y::CardClass[1]->NewObject());

	FightInfo->MCSkill = MakeShared<NormalSkill>();
}


void UY_GameInstance::EndRoom()
{
	Y::Log(0, TEXT("EndRoom"));

	if (IsValid(Y::GetMainCharacter()))Y::GetMainCharacter()->Destroy();
	Y::GetMainCharacter() = nullptr;
	for (auto& p : Y::GetEnemys())if (IsValid(p))p->Destroy();
	Y::GetEnemys().Empty();
	for (auto& p : Y::GetCards())if (IsValid(p))p->Destroy();
	Y::GetCards().Empty();
	for (auto& p : Y::GetFloors())if (IsValid(p))p->Destroy();
	Y::GetFloors().Empty();
	if(IsValid(UY_RoomWidget::CurrentRoom))
		UY_RoomWidget::CurrentRoom->FightEnd();
	UY_RoomWidget::CurrentRoom = nullptr;
}

void UY_GameInstance::ChangeTopoRate(float MultiplyRate)
{
	TopoRate *= MultiplyRate;
}


void UY_GameInstance::AddAtk(AY_Character* owner)
{
	if(IsValid(UY_TimeLine::YTimeLine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Call AddCharacterProfile"));
		//Correct On first Run. Will Crash on the next. Maybe the order of BeginPlay effect it.
		//UY_TimeLine::YTimeLine->AddCharacterProfile(owner);
		UY_TimeLine::YTimeLine->AddCharacter(owner);
	}

	for (int32 i = 0; i < AtkOrder.Num(); i++) {
		if (owner->CharacterAttackTime<AtkOrder[i]->CharacterAttackTime ||
			owner->CharacterAttackTime == AtkOrder[i]->CharacterAttackTime &&
			owner->CharacterPriority> AtkOrder[i]->CharacterPriority) {
			AtkOrder.Insert(owner, i);
			return;
		}
	}
	AtkOrder.Add(owner);
}

void UY_GameInstance::HelpTick(float DeltaTime)
{
	RunTime += DeltaTime; 
	UY_TimeLine::YTimeLine->UpdateTimeMark();
	if (RunTime > TickTime) {
		TickTime += 20;
		for (auto& p : Enemys)
		{
			if(p->Buffs->ExecuteBuffs(p, p, *(p->Buffs), Y_Buff::BeginTick, TEXT("Tick")))
			{
				p->Buffs->ExecuteBuffs(p, p, *(p->Buffs), Y_Buff::Ticking, TEXT("Tick"));
				p->Buffs->ExecuteBuffs(p, p, *(p->Buffs), Y_Buff::AfterTick, TEXT("Tick"));
			}
		}
		Y::GetGameInfo()->EventBuffs.ExecuteBuffs(nullptr, nullptr, Y::GetGameInfo()->EventBuffs, Y_Buff::Ticking, TEXT("Tick"));
		Y::GetGameInfo()->EquipmentBuffs.ExecuteBuffs(nullptr, nullptr, Y::GetGameInfo()->EquipmentBuffs, Y_Buff::Ticking, TEXT("Tick"));
		Y::GetGameInfo()->ToExecuteBuffs.ExecuteBuffs(nullptr, nullptr, Y::GetGameInfo()->ToExecuteBuffs, Y_Buff::Ticking, TEXT("Tick"));
	}
	//while (AtkOrder.Num() > 0) {
	//	if(!IsValid(AtkOrder[0]))
	//	{
	//		AtkOrder.RemoveAt(0);
	//		continue;
	//	}
	//	else {
	//		if (RunTime * 10 >= AtkOrder[0]->CharacterAttackTime) {
	//			AtkOrder[0]->Attack();
	//			AtkOrder.RemoveAt(0);
	//		}
	//		else break;
	//	}
	//}
}

void UY_GameInstance::DeleteAtk(AY_Character* owner)
{
	AtkOrder.Remove(owner);
}


UTexture2D* UY_GameInstance::LoadPicture(const FString& FilePath)
{
	if (Pictures.Contains(FilePath))
		return *Pictures.Find(FilePath);
	//判断地址为空
	auto& ImagePath = FilePath;
	if (ImagePath.IsEmpty()) {
		return nullptr;
	}
	if (!ImagePath.EndsWith(".png") && !ImagePath.EndsWith(".jpg") && !ImagePath.EndsWith(".jpeg")) {
		Y::Log(0, TEXT("LoadSuccessfully"));
		auto P =  LoadObject<UTexture2D>(nullptr, ImagePath.GetCharArray().GetData());
		if (IsValid(P))
		{
			Pictures.Add(FilePath, P);
			return P;
		}
	}

	//判断是否存在文件,文件是否能转为数组
	TArray<uint8> CompressedData;
	if (!FFileHelper::LoadFileToArray(CompressedData, *ImagePath)) {
		return nullptr;
	}

	//判断文件格式
	EImageFormat imageformat = EImageFormat::Invalid;
	if (ImagePath.EndsWith(".png"))
		imageformat = EImageFormat::PNG;
	else if (ImagePath.EndsWith(".jpg") || ImagePath.EndsWith(".jpeg"))
		imageformat = EImageFormat::JPEG;
	else
	{
		return nullptr;
	}

	//创建图片封装器
	IImageWrapperModule& imageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("IMageWrapper"));
	TSharedPtr<IImageWrapper> imageWrapper = imageWrapperModule.CreateImageWrapper(imageformat);

	//解码图片
	//获取图片信息
	if (!imageWrapper->SetCompressed(CompressedData.GetData(), CompressedData.Num())) {

		return nullptr;
	}

	//创建纹理
	TArray<uint8> UncompressedRGBA;
	if (!imageWrapper->GetRaw(ERGBFormat::RGBA, 8, UncompressedRGBA))
		return nullptr;

	UTexture2D* texture2d = UTexture2D::CreateTransient(imageWrapper->GetWidth(), imageWrapper->GetHeight(), PF_R8G8B8A8);
	if (!texture2d)
		return nullptr;

	//赋值纹理
	void* texturedata = texture2d->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(texturedata, UncompressedRGBA.GetData(), UncompressedRGBA.Num());
	texture2d->GetPlatformData()->Mips[0].BulkData.Unlock();

	texture2d->UpdateResource();

	Pictures.Add(FilePath, texture2d);

	return texture2d;
}
