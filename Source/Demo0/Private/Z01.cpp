// Fill out your copyright notice in the Description page of Project Settings.


#include "Z01.h"
#include "Y.h"
#include "Y_ClassBase.h"
#include "Y_Character.h"
#include "Y_Fighting.h"
#include "CameraPawn.h"
#include "Y_EventWidget.h"
#include "Y_ChoiceWidget.h"
#include "Y_PlayerController.h"
#include "Y_Settle.h"
#include "Y_Trophy.h"
#include "Y_Equipment.h"
#include "Y_ChooseCard.h"
#include "Y_PlayerController.h"
#include "Y.h"
#include "I01.h"


void LZ01()
{
	Y::LoadRoom<E01>(1);
}

E01::E01()
{
	RoomID = 101;
}
TSharedPtr<Y_RoomInfo> E01::RoomClicked()
{

	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生成地板
	}

	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置
	auto EP = MakeShared<Y_EventInfo>();

	EP->Description = Y::PrintText(TEXT("少年，买卡删卡了解一下"));
	if (Y::GetGameInfo()->MoneyCount() >= 50)
	{
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("购买卡牌")), []()
			{
				Y::GetGameInfo()->MoneyCount() -= 50;
				GetNewCard();
			}));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("删除卡牌")), []()
			{
				Y::GetGameInfo()->MoneyCount() -= 50;
				DeleteCard();
			}));
	}
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("继续旅途")), []() {}));

	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E02::E02()
{
	RoomID = 102;
}
TSharedPtr<Y_RoomInfo> E02::RoomClicked()
{
	for (int32 i = 0; i < 10; i++)
	{
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);
	}

	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);
	auto EP = MakeShared<Y_EventInfo>();
	auto EP1 = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("瀑布修炼"));
	EP1->Description = Y::PrintText(TEXT("是否再次修炼，消耗10点生命值"));
	if (Y::GetMainCharacter()->Health > 5)
	{
		if (Y::getRandom() < 0.6)
		{
			EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("消耗5点生命值删除一张卡")), []()
				{
					Y::GetMainCharacter()->Health -= 5;
					DeleteCard();
				}, EP1));
		}
		else
		{
			EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("消耗5点生命值删除一张卡")), []()
				{
					Y::GetMainCharacter()->Health -= 5;
					DeleteCard();
				}));
		}
	}
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	if (Y::GetMainCharacter()->Health > 10)
	{
		EP1->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("还不够！")), []()
			{
				Y::GetMainCharacter()->Health -= 10;
				DeleteCard();
			}));
	}
	EP1->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));

	Y::GetController()->BeginEvent(EP);

	return nullptr;
}

E03::E03()
{
	RoomID = 103;
}
TSharedPtr<Y_RoomInfo> E03::RoomClicked()
{
	for (int32 i = 0; i < 10; i++)
	{
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);
	}
	auto EP = MakeShared<Y_EventInfo>();
	auto EP1 = MakeShared<Y_EventInfo>();
	auto EP2 = MakeShared<Y_EventInfo>();
	auto EP3 = MakeShared<Y_EventInfo>();

	EP->Description = Y::PrintText(TEXT("福报？"));
	EP1->Description = Y::PrintText(TEXT("福报again？"));
	EP2->Description = Y::PrintText(TEXT("福报once more？"));
	EP3->Description = Y::PrintText(TEXT("福报来喽！"));

	if (Y::GetMainCharacter()->Health > 3)
	{
		if (Y::getRandom() < 0.3)
		{
			EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取福报")), []()
				{
					Y::GetMainCharacter()->Health -= 3;
					Y::GetGameInfo()->MoneyCount() += 96;
				}));
		}
		else
		{
			EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取福报")), []()
				{
					Y::GetMainCharacter()->Health -= 3;
				}, EP1));
		}
	}
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));

	if (Y::GetMainCharacter()->Health > 6)
	{
		if (Y::getRandom() < 0.5)
		{
			EP1->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取福报")), []()
				{
					Y::GetMainCharacter()->Health -= 6;
					Y::GetGameInfo()->MoneyCount() += 96;
				}));
		}
		else
		{
			EP1->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取福报")), []()
				{
					Y::GetMainCharacter()->Health -= 6;
				}, EP2));
		}
	}
	EP1->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));

	if (Y::getRandom() < 0.7)
	{
		if (Y::GetMainCharacter()->Health)
		{
			EP2->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取福报")), []()
				{
					Y::GetMainCharacter()->Health -= 9;
					Y::GetGameInfo()->MoneyCount() += 96;
				}));
		}
		else
		{
			EP2->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取福报")), []()
				{
					Y::GetMainCharacter()->Health -= 9;
				}, EP3));
		}
	}
	EP2->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));

	EP3->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取福报")), []()
		{
			Y::GetGameInfo()->UsingCards.Add(MakeShared<C2003>());//诅咒
			//Temp
			Y::GetGameInfo()->ReadyRooms.Add(MakeShared<E04>());
		}));
	EP3->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E04::E04()
{
	RoomID = 104 + 1000;
}
TSharedPtr<Y_RoomInfo> E04::RoomClicked()
{
	for (int32 i = 0; i < 10; i++)
	{
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);
	}
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("报官"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("确定")), []()
		{
			//Temp
			Y::GetGameInfo()->MoneyCount() += 100;
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("威胁而获得100G")), []()
		{
			Y::GetGameInfo()->MoneyCount() += 100 + 10 * Y::getRandom();
		}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E05::E05()
{
	RoomID = 105;
}
TSharedPtr<Y_RoomInfo> E05::RoomClicked()
{
	for (int32 i = 0; i < 10; i++)
	{
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);
	}
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("身上没钱了，该怎么办呢？"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("还是先苦一苦百姓吧...")), [this]()
		{
			this->ChangeEndType(2);
			Y::GetGameInfo()->SettleInfo->TrophyInfos.Add(MakeShared<MoneyTrophy>(80 + Y::getRandom() * 40));
		}));

	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E06::E06()
{
	RoomID = 106;
}
TSharedPtr<Y_RoomInfo> E06::RoomClicked()
{
	for (int32 i = 0; i < 10; i++)
	{
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto TC1 = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[8]);//敌人
	TC1->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC1->Update();

	TArray<TSharedPtr<Y_EventInfo>> EA;
	for (int32 i = 0; i < 3; i++) {
		auto p = MakeShared<Y_EventInfo>();
		p->Description = Y::PrintText(TEXT("战场寻迹"));
		float r = Y::getRandom();
		p->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("捡")), [i, r, this]() {
			if (r < 0.5 - 0.1 * i) {
				Y::GetGameInfo()->AddEquipment(Y::GetGameInfo()->GetRandomEquipment());
			}
			else if (r < 2 * (0.5 - 0.1 * i)) {
				this->ChangeEndType(2);
			}}, (r > 2 * (0.5 - 0.1 * i) ? EA[i - 1] : nullptr)));
		p->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("")), []() {}));
	}
	Y::GetController()->BeginEvent(EA[2]);
	return nullptr;
}

E07::E07()
{
	RoomID = 107;
}
TSharedPtr<Y_RoomInfo> E07::RoomClicked()
{
	for (int32 i = 0; i < 10; i++)
	{
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("叛徒"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("消耗100G获取稀有卡牌")), []()
		{
			Y::GetGameInfo()->MoneyCount() -= 100;
			TArray<TSharedPtr<Y_CardInfo>> CA;
			while (CA.Num() < 3) {
				auto p = Y::GetGameInfo()->GetRandomCard();
				if (p->CardRare > 1)CA.Add(p);
			}
			auto p = MakeShared<Y_ChooseCardIN>();
			p->Cards = CA;
			Y::GetController()->BeginChoose(p);
			//Temp
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E08::E08()
{
	RoomID = 108;
}
TSharedPtr<Y_RoomInfo> E08::RoomClicked()
{
	for (int32 i = 0; i < 10; i++)
	{
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);
	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("讲武堂"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获得100G和疑虑")), []()
		{
			Y::GetGameInfo()->UsingCards.Add(MakeShared<C2001>());//疑虑
			Y::GetGameInfo()->MoneyCount() += 100;
			Y::GetGameInfo()->ReadyRooms.Add(MakeShared<E09>());
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E09::E09()
{
	RoomID = 109 + 1000;
}
TSharedPtr<Y_RoomInfo> E09::RoomClicked()
{
	for (int32 i = 0; i < 10; i++)
	{
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);
	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("E08衍生"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("去除疑虑，获得一张卡")), []()
		{
			for (auto& p : Y::GetGameInfo()->InHandCards)
			{
				if (p->CardID == 2001)
				{
					Y::GetGameInfo()->InHandCards.Remove(p);
					break;
				}
			}//去除疑虑
			//Temp
			GetNewCard();
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E10::E10()
{
	RoomID = 110;
}
TSharedPtr<Y_RoomInfo> E10::RoomClicked()
{
	for (int32 i = 0; i < 10; i++)
	{
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("勾结"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取50G")), []()
		{
			Y::GetGameInfo()->MoneyCount() += 50;
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取100G")), [this]()
		{
			this->ChangeEndType(2);
			Y::GetGameInfo()->SettleInfo->TrophyInfos.Add(MakeShared<MoneyTrophy>(100));
		}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E11::E11()
{
	RoomID = 111;
}
TSharedPtr<Y_RoomInfo> E11::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("此路是我开，此树是我栽"));
	if (Y::GetGameInfo()->MoneyCount() > 0)
	{
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("大爷别动手，我有钱")), []()
			{
				Y::GetGameInfo()->MoneyCount() -= Y::GetGameInfo()->MoneyCount() * 0.5;
			}));
	}
	if (Y::GetMainCharacter()->Health > 10)
	{
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("要钱没有，要命一条")), []()
			{
				Y::GetMainCharacter()->Health -= 10;
			}));
	}
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E12::E12()
{
	RoomID = 112;
}
TSharedPtr<Y_RoomInfo> E12::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("黄雀在后"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("战斗")), [this]()
		{
			auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[1]);//敌人
			TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
			TC->Update();
			this->ChangeEndType(2);
			Y::GetGameInfo()->SettleInfo->TrophyInfos.Add(MakeShared<MoneyTrophy>(100 + Y::getRandom() * 50));
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E13::E13()
{
	RoomID = 113;
}
TSharedPtr<Y_RoomInfo> E13::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("见习长老"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取随机一张卡牌")), []()
		{
			Y::GetGameInfo()->UsingCards.Add(Y::GetGameInfo()->GetRandomCard());
			Y::GetGameInfo()->MoneyCount() += (50 + Y::getRandom() * 30);
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));

	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E14::E14()
{
	RoomID = 114;
}
TSharedPtr<Y_RoomInfo> E14::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("点拨"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("确定")), []()
		{
			Y::GetMainCharacter()->Health -= (Y::GetMainCharacter()->Health * 0.2);
			Y::GetMainCharacter()->Health += (Y::GetMainCharacter()->MaxHealth * 0.2);
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E15::E15()
{
	RoomID = 201;
}
TSharedPtr<Y_RoomInfo> E15::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("试药"));
	if (Y::GetMainCharacter()->Health > 15)
	{
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("确定")), []()
			{
				Y::GetMainCharacter()->Health -= 15 + Y::getRandom() * 20;
				Y::GetGameInfo()->MoneyCount() += 50;
			}));
	}
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E16::E16()
{
	RoomID = 202;
}
TSharedPtr<Y_RoomInfo> E16::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto p = Y::GetGameInfo()->GetRandomEquipment();
	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("发现卧底"));
	auto EP1 = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("你要这个%s吗？"), Y::toS(p->EquipmentName));
	EP1->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("当然要")), [p]()
		{
			Y::GetGameInfo()->AddEquipment(p);
		}));
	EP1->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("什么垃圾")), []() {}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("揭露")), []()
		{
			Y::GetGameInfo()->MoneyCount() += 50 + Y::getRandom() * 10;
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("威胁")), [this]()
		{
			if (Y::getRandom() < 0.3)
			{
				this->ChangeEndType(2);
			}
			else {}
		}, EP1));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("无视")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E17::E17()
{
	RoomID = 203;
}
TSharedPtr<Y_RoomInfo> E17::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("发现卧底"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("配合")), [this]()
		{
			this->ChangeEndType(2);
			Y::GetGameInfo()->SettleInfo->TrophyInfos.Add(MakeShared<MoneyTrophy>(100 + Y::getRandom() * 50));
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("揭发")), []()
		{
			Y::GetGameInfo()->UsingCards.Add(MakeShared<C2005>());
			Y::GetGameInfo()->MoneyCount() += 100 + Y::getRandom() * 50;
		}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E18::E18()
{
	RoomID = 204;
}
TSharedPtr<Y_RoomInfo> E18::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("老乞丐"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("施舍")), []()
		{
			Y::GetGameInfo()->MoneyCount() -= 100;
			Y::GetGameInfo()->ReadyRooms.Add(MakeShared<E19>());
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E19::E19()
{
	RoomID = 205 + 1000;
}
TSharedPtr<Y_RoomInfo> E19::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto p2 = Y::GetGameInfo()->GetRandomEquipment();
	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("乞丐的回报"));
	//Temp
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("装备:%s"), Y::toS(p2->EquipmentName)), [p2]()
		{
			Y::GetGameInfo()->AddEquipment(p2);
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获得卡")), []()
		{
			GetNewCard();
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("高级强化")), []()
		{
			Y::GetGameInfo()->EquipmentUpgrades(2);
		}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E20::E20()
{
	RoomID = 206;
}
TSharedPtr<Y_RoomInfo> E20::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("参赛守卫"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("确定")), []()
		{
			auto eqm = Y::GetGameInfo()->Equipments[int32(Y::getRandom() * Y::GetGameInfo()->Equipments.Num())];
			Y::PrintText(TEXT("失去%s"), Y::toS(eqm->EquipmentName));
			Y::GetGameInfo()->RemoveEquipment(eqm);
			Y::GetGameInfo()->MoneyCount() += 50;
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E21::E21()
{
	RoomID = 207;
}//Need Fix
TSharedPtr<Y_RoomInfo> E21::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("老铁匠"));
	auto TA = Y::GetRandomArray(Y::GetGameInfo()->EquipmentUpgrades(1));
	if (Y::GetGameInfo()->MoneyCount() > 100) {
		for (auto& p : TA)EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("强化为： %s"), Y::toS(p->EquipmentName)), [p, EP]() {
			Y::GetGameInfo()->AddEquipment(p);
			}));
	}
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("离开")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E22::E22()
{
	RoomID = 208;
	Choosed = false;
}
TSharedPtr<Y_RoomInfo> E22::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("这是一场试炼"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("确定")), [this]()
		{
			Y::GetGameInfo()->ReadyRooms.Add(MakeShared<E23>());
			Choosed = true;
			this->ChangeEndType(2);
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}
void E22::LeaveRoom()
{
	if (Choosed)
	{
		ChangeEndType(3);
		auto EP = MakeShared<Y_EventInfo>();
		EP->Description = Y::PrintText(TEXT("试炼的奖励"));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("恢复20%生命值")), []()
			{
				Y::GetMainCharacter()->Health += Y::GetMainCharacter()->MaxHealth * 0.2;
			}));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("删除一张卡")), []()
			{
				DeleteCard();
			}));
	}
	else
	{
		DoToEndRoom();
	}
}

E23::E23()
{
	RoomID = 209 + 1000;
	Choosed = false;
}
TSharedPtr<Y_RoomInfo> E23::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("又是一场试炼"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("确定")), [this]()
		{
			Y::GetGameInfo()->ReadyRooms.Add(MakeShared<E24>());
			this->ChangeEndType(2);
			Choosed = true;
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}
void E23::LeaveRoom()
{
	if (Choosed)
	{
		ChangeEndType(3);
		auto p2 = Y::GetGameInfo()->GetRandomEquipment();
		auto EP = MakeShared<Y_EventInfo>();
		EP->Description = Y::PrintText(TEXT("试炼的奖励"));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取一件装备%s"), Y::toS(p2->EquipmentName)), [p2]()
			{
				Y::GetGameInfo()->AddEquipment(p2);
			}));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	}
}

E24::E24()
{
	RoomID = 210 + 1000;
	Choosed = false;
}
TSharedPtr<Y_RoomInfo> E24::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("最终的试炼"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("确定")), [this]()
		{
			this->ChangeEndType(2);
			Choosed = true;
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}
void E24::LeaveRoom()
{
	if (Choosed)
	{
		ChangeEndType(3);
		auto EP = MakeShared<Y_EventInfo>();
		EP->Description = Y::PrintText(TEXT("试炼的奖励"));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("高级强化")), []()
			{
				Y::GetGameInfo()->EquipmentUpgrades(2);
			}));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	}
}

E25::E25()
{
	RoomID = 211;
}
TSharedPtr<Y_RoomInfo> E25::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("野心"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("加入组织")), []()
		{
			Y::GetGameInfo()->MoneyCount() -= 50;
			Y::GetGameInfo()->ReadyRooms.Add(MakeShared<E26>());
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}


E26::E26()
{
	RoomID = 212 + 1000;
	Choosed = false;
}
TSharedPtr<Y_RoomInfo> E26::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("抉择"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("战斗")), [this]()
		{
			this->ChangeEndType(2);
			Choosed = true;
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("背叛")), []()
		{
			Y::GetGameInfo()->MoneyCount() += 100;
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}
void E26::LeaveRoom()
{
	if (Choosed)
	{
		ChangeEndType(3);
		auto EP = MakeShared<Y_EventInfo>();
		auto p1 = Y::GetGameInfo()->GetRandomEquipment();
		auto p2 = Y::GetGameInfo()->GetRandomEquipment();
		auto p3 = Y::GetGameInfo()->GetRandomEquipment();
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取一件装备%s"), Y::toS(p1->EquipmentName)), [p1]()
			{
				Y::GetGameInfo()->AddEquipment(p1);
			}));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取一件装备%s"), Y::toS(p2->EquipmentName)), [p2]()
			{
				Y::GetGameInfo()->AddEquipment(p2);
			}));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获取一件装备%s"), Y::toS(p3->EquipmentName)), [p3]()
			{
				Y::GetGameInfo()->AddEquipment(p3);
			}));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	}
}


E27::E27()
{
	RoomID = 301;
}
TSharedPtr<Y_RoomInfo> E27::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("刺激"));

	auto c1 = Y::GetGameInfo()->UsingCards[int(Y::getRandom() * Y::GetGameInfo()->UsingCards.Num())];
	auto c2 = Y::GetGameInfo()->UsingCards[int(Y::getRandom() * Y::GetGameInfo()->UsingCards.Num())];
	auto c3 = Y::GetGameInfo()->UsingCards[int(Y::getRandom() * Y::GetGameInfo()->UsingCards.Num())];
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("确定,%s"), Y::toS(c1->CardName)), [c1]()
		{
			Y::GetGameInfo()->UsingCards.Remove(c1);
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("确定,%s"), Y::toS(c2->CardName)), [c2]()
		{
			Y::GetGameInfo()->UsingCards.Remove(c2);
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("确定,%s"), Y::toS(c3->CardName)), [c3]()
		{
			Y::GetGameInfo()->UsingCards.Remove(c3);
		}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E28::E28()
{
	RoomID = 302;
}
TSharedPtr<Y_RoomInfo> E28::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("逃亡指挥官"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("帮助他")), [this]()
		{
			Y::GetGameInfo()->ReadyRooms.Add(MakeShared<E29>());
			this->ChangeEndType(2);
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E29::E29()
{
	RoomID = 303 + 1000;
}
TSharedPtr<Y_RoomInfo> E29::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("指挥官的回报"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("金币200G")), []()
		{
			Y::GetGameInfo()->MoneyCount() += 200;
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("装备全升为2级")), []()
		{
			for (int32 i = 0; i < Y::GetGameInfo()->Equipments.Num(); i++)
			{
				if (Y::GetGameInfo()->Equipments[i]->EquipLevel == 1)
				{
					auto p = Y::GetGameInfo()->Equipments[i]->Upgrade();
					Y::GetGameInfo()->Equipments[i] = p[0];
				}
			}
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("金币200G")), []()
		{
			Y::GetGameInfo()->EquipmentUpgrades(2);
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E30::E30()
{
	RoomID = 304;
}
TSharedPtr<Y_RoomInfo> E30::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("隐秘行动"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("不作声")), [this]()
		{
			if (Y::getRandom() < 0.4)
			{
				this->ChangeEndType(2);
			}
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("离开")), []()
		{
			Y::GetMainCharacter()->Health -= Y::GetMainCharacter()->Health * 0.2;
		}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E31::E31()
{
	RoomID = 305;
}
TSharedPtr<Y_RoomInfo> E31::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("人性"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("默不作声")), [this]()
		{
			Y::GetGameInfo()->MoneyCount() += 120 + Y::getRandom() * 10;
			if (Y::getRandom() < 0.2 + 0.01 * (1 - Y::GetMainCharacter()->Health / Y::GetMainCharacter()->MaxHealth))
			{
				this->ChangeEndType(2);
			}
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("出手相助")), [this]()
		{
			Y::GetGameInfo()->MoneyCount() -= 120 + Y::getRandom() * 10;
			for (auto& p : Y::GetGameInfo()->InHandCards)
			{
				if (p->CardTypes.Contains(10))
					Y::GetGameInfo()->InHandCards.Remove(p);
			}
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E32::E32()
{
	RoomID = 306;
}
TSharedPtr<Y_RoomInfo> E32::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto p1 = Y::GetGameInfo()->GetRandomEquipment();
	auto t1 = p1->Upgrade();
	auto p2 = Y::GetGameInfo()->GetRandomEquipment();
	auto t2 = p1->Upgrade();
	auto p3 = Y::GetGameInfo()->GetRandomEquipment();
	auto t3 = p1->Upgrade();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("收尸人"));
	if (Y::GetGameInfo()->MoneyCount() >= 250)
	{
		Y::GetGameInfo()->AddEquipment(t1[0]);
		//EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("购买二级装备%s"), Y::toS(t1[0]->EquipmentName)), [](){},UpgradeEquipment(1)));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("购买二级装备%s"), Y::toS(t1[0]->EquipmentName)), [t1]()
			{
				auto t = t1;
				Y::GetGameInfo()->MoneyCount() -= 250;
				Y::GetGameInfo()->AddEquipment(t[0]);
			}));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("购买二级装备%s"), Y::toS(t2[0]->EquipmentName)), [t2]()
			{
				auto t = t2;
				Y::GetGameInfo()->MoneyCount() -= 250;
				Y::GetGameInfo()->AddEquipment(t[0]);
			}));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("购买二级装备%s"), Y::toS(t3[0]->EquipmentName)), [t3]()
			{
				auto t = t3;
				Y::GetGameInfo()->MoneyCount() -= 250;
				Y::GetGameInfo()->AddEquipment(t[0]);
			}));
	}
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E33::E33()
{
	RoomID = 307;
}//Need Fix
TSharedPtr<Y_RoomInfo> E33::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	auto TA = Y::GetRandomArray(Y::GetGameInfo()->EquipmentUpgrades(2));
	if (Y::GetGameInfo()->MoneyCount() > 250) {
		for (auto& p : TA)EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("强化为： %s"), Y::toS(p->EquipmentName)), [p, EP]() {
			Y::GetGameInfo()->AddEquipment(p);
			}));
	}
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("离开")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E34::E34()
{
	RoomID = 308;
}
TSharedPtr<Y_RoomInfo> E34::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	//Need Fix
	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("医院"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("恢复状态")), [EP]()
		{

		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E35::E35()
{
	RoomID = 11;
}
TSharedPtr<Y_RoomInfo> E35::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("装备刷新"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("刷新")), []()
		{
			for (auto& p : Y::GetGameInfo()->Equipments)
				p->CanUsed();
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E36::E36()
{
	RoomID = 12;
}
TSharedPtr<Y_RoomInfo> E36::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("功德箱"));
	if (Y::GetGameInfo()->MoneyCount() >= 50)
	{
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("50G删卡")), []()
			{
				Y::GetGameInfo()->MoneyCount() -= 50;
				DeleteCard();
			}));
	}
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获得200G,和诅咒")), []()
		{
			Y::GetGameInfo()->MoneyCount() += 200;
			Y::GetGameInfo()->UsingCards.Add(MakeShared<C2005>());
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E37::E37()
{
	RoomID = 13;
}
TSharedPtr<Y_RoomInfo> E37::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("云游铁匠"));
	if (Y::GetGameInfo()->MoneyCount() >= 100)
	{
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("100块的强化")), []()
			{
				Y::GetGameInfo()->MoneyCount() -= 100;
				Y::GetGameInfo()->EquipmentUpgrades(1);
			}));
	}
	if (Y::GetGameInfo()->MoneyCount() >= 200)
	{
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("200块的强化")), []()
			{
				Y::GetGameInfo()->MoneyCount() -= 200;
				Y::GetGameInfo()->EquipmentUpgrades(2);
			}));
	}
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E38::E38()
{
	RoomID = 14;
}
TSharedPtr<Y_RoomInfo> E38::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("篝火"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("回复生命值")), []()
		{
			Y::GetMainCharacter()->Health += 0.3 * Y::GetMainCharacter()->MaxHealth;
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获得卡牌")), []()
		{
			GetNewCard();
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E39::E39()
{
	RoomID = 15;
}
TSharedPtr<Y_RoomInfo> E39::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto p1 = Y::GetGameInfo()->GetRandomEquipment();
	auto p2 = Y::GetGameInfo()->GetRandomEquipment();
	auto p3 = Y::GetGameInfo()->GetRandomEquipment();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("装备商人"));
	if (Y::GetGameInfo()->MoneyCount() >= 100)
	{
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("购买%s"), Y::toS(p1->EquipmentName)), [p1]()
			{
				Y::GetGameInfo()->MoneyCount() -= 100;
				Y::GetGameInfo()->AddEquipment(p1);
			}));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("购买%s"), Y::toS(p2->EquipmentName)), [p2]()
			{
				Y::GetGameInfo()->MoneyCount() -= 100;
				Y::GetGameInfo()->AddEquipment(p2);
			}));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("购买%s"), Y::toS(p3->EquipmentName)), [p3]()
			{
				Y::GetGameInfo()->MoneyCount() -= 100;
				Y::GetGameInfo()->AddEquipment(p3);
			}));
	}
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E40::E40()
{
	RoomID = 16;
}
TSharedPtr<Y_RoomInfo> E40::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("对赌"));

	if (Y::GetGameInfo()->MoneyCount() > 0)
	{
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("开赌")), []()
			{
				Y::GetGameInfo()->MoneyCount() -= Y::GetGameInfo()->MoneyCount() * 0.5;
				if (Y::getRandom() < 0.5)
				{
					Y::GetGameInfo()->MoneyCount() += Y::GetGameInfo()->MoneyCount() * 2;
				}
			}));
	}
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E41::E41()
{
	RoomID = 17;
}
TSharedPtr<Y_RoomInfo> E41::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();


	auto p = Y::GetGameInfo()->GetRandomEquipment();
	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("宝库"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("删卡")), []()
		{
			DeleteCard();
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获得装备%s"), Y::toS(p->EquipmentName)), [p]()
		{
			Y::GetGameInfo()->AddEquipment(p);
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("获得100块")), []()
		{
			Y::GetGameInfo()->MoneyCount() += 100 + Y::getRandom() * 50;
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E42::E42()
{
	RoomID = 18;
}
TSharedPtr<Y_RoomInfo> E42::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("陷阱"));
	if (Y::GetMainCharacter()->Health > 5)
	{
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("失去5点生命值")), []()
			{
				Y::GetMainCharacter()->Health -= 5;
			}));
	}
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("失去5点生命值上限")), []()
		{
			Y::GetMainCharacter()->MaxHealth -= 5;
		}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E43::E43()
{
	RoomID = 19;
}
TSharedPtr<Y_RoomInfo> E43::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("蘑菇"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("50G")), []()
		{
			Y::GetGameInfo()->MoneyCount() += 50;
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("掉15%H回等量Max")), []()
		{
			Y::GetMainCharacter()->Health -= Y::GetMainCharacter()->Health * 0.15;
			Y::GetMainCharacter()->Health += Y::GetMainCharacter()->MaxHealth * 0.15;
		}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("掉10%maxH回等量H")), []()
		{
			Y::GetMainCharacter()->Health -= Y::GetMainCharacter()->MaxHealth * 0.1;
			Y::GetMainCharacter()->Health += Y::GetMainCharacter()->Health * 0.1;
		}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}

E44::E44()
{
	RoomID = 20;
}
TSharedPtr<Y_RoomInfo> E44::RoomClicked()
{
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);//生产地板
	}
	Y::GetGameInfo()->ReadyRooms.Add(MakeShared<EventRoom>());
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);//主角位置

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);//敌人
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("疗养师"));
	if (Y::GetGameInfo()->MoneyCount() >= 50)
	{
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("消耗50G恢复生命")), []()
			{
				Y::GetGameInfo()->MoneyCount() -= 50;
				Y::GetMainCharacter()->Health += 0.2 * Y::GetMainCharacter()->Health;
			}));
		EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("消耗50G删卡")), []()
			{
				Y::GetGameInfo()->MoneyCount() -= 50;
				DeleteCard();
			}));
	}
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("放弃")), []() {}));
	Y::GetController()->BeginEvent(EP);
	return nullptr;
}