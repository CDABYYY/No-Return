// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DEMO0_API Y
{
public:
	Y();
	~Y();
	static class UY_GameInstance*& GetGameInstance();

	static class ACameraPawn*& GetPlayer();

	static class AY_Character*& GetMainCharacter();

	static class AY_PlayerController*& GetController();

	static class Y_Fighting* GetGameInfo();

	static TArray<class AY_Card*>& GetCards();

	static TArray<class AY_Floor*>& GetFloors();

	static TArray<class AY_Character*>& GetEnemys();

	static FVector& GetLocation();

	static FRotator& GetRotation();

	static int32 ExecutePureAction(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, FString TriggerAction, bool TryAttack = false);

	static int32 ExecuteAction(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, FString TriggerAction, bool TryAttack = false);

	static float getRandom();

	static class UWorld* GetWorld();

	template<typename ...Argv>
	static void Log(bool test, const TCHAR Format[], Argv... Params) {
		FString s = FString::Printf(Format, Params...);
		GetGameInstance()->GetEngine()->AddOnScreenDebugMessage(-1, 10, FColor::Red, s);
		//UE_LOG(LogTemp, Warning, Format, Params...);
	}

	template<typename ...Argv>
	static void Log(const TCHAR Format[], Argv... Params) {
		FString s = FString::Printf(Format, Params...);
		GetGameInstance()->GetEngine()->AddOnScreenDebugMessage(-1, 5, FColor::Blue, s);
		//UE_LOG(LogTemp, Warning, Format, Params...);
	}

	template<typename T>
	static T getRandom(TMap<T, float> m) {
		float tot = 0;
		for (auto&& p : m)tot += p.Value;
		float choosed = getRandom() * tot;
		for (auto&& p : m) {
			if (choosed < p.Value)return p.Key;
			choosed -= p.Value;
		}
		return m.begin()->Key;
	}
	

	template<class T1>
	class Y_SubClassIF {
	public:
		template<class...Argv>
		TSharedPtr<T1> NewObject(Argv...argv) {
			TSharedPtr<T1> TmpP = NewObject();
			TmpP->Init(argv...);
			return TmpP;
		}
		template<>
		TSharedPtr<T1> NewObject() { return NewObject(); }

		virtual TSharedPtr<T1> NewObject() = 0;
		virtual ~Y_SubClassIF() {};
	};


	template<class T2, class T3>
	class Y_SubClassIM :public Y_SubClassIF<T2> {
	public:
		TSharedPtr<T2> NewObject()override {
			return MakeShared<T3>();
		}
	};
	
	template<class T1,class T2>
	static TUniquePtr<Y_SubClassIF<T1>> StoreClass() {
		return MakeUnique<Y_SubClassIM<T1, T2>>();
	}

	static TMap<int32, TUniquePtr<Y_SubClassIF<class Y_CardInfo>>>& CardInfos(int32 ID = -1, TUniquePtr<Y_SubClassIF<class Y_CardInfo>> StoredClass = nullptr){
		static TMap<int32,TUniquePtr<Y_SubClassIF<class Y_CardInfo>>> Cardclass;
		if (ID > 0) {
			Cardclass.Add(ID, MoveTemp(StoredClass));
		}
		return Cardclass;
	};

	static TMap<int32, TUniquePtr<Y_SubClassIF<class Y_EnemyInfo>>>& CharacterInfos(int32 ID = -1, TUniquePtr<Y_SubClassIF<class Y_EnemyInfo>> StoredClass = nullptr) {
		static TMap<int32, TUniquePtr<Y_SubClassIF<class Y_EnemyInfo>>> Cardclass;
		if (ID > 0) {
			Cardclass.Add(ID, MoveTemp(StoredClass));
		}
		return Cardclass;
	};

	static TMap<int32, TUniquePtr<Y_SubClassIF<class Y_FloorInfo>>>& FloorInfos(int32 ID = -1, TUniquePtr<Y_SubClassIF<class Y_FloorInfo>> StoredClass = nullptr) {
		static TMap<int32, TUniquePtr<Y_SubClassIF<class Y_FloorInfo>>> Cardclass;
		if (ID > 0) {
			Cardclass.Add(ID, MoveTemp(StoredClass));
		}
		return Cardclass;
	};

	static TMap<int32, TUniquePtr<Y_SubClassIF<class Y_RoomInfo>>>& RoomInfos(int32 ID = -1, TUniquePtr<Y_SubClassIF<class Y_RoomInfo>> StoredClass = nullptr) {
		static TMap<int32, TUniquePtr<Y_SubClassIF<class Y_RoomInfo>>> Cardclass;
		if (ID > 0) {
			Cardclass.Add(ID, MoveTemp(StoredClass));
		}
		return Cardclass;
	};

	static TMap<int32, TUniquePtr<Y_SubClassIF<class Y_Buff>>>& BuffInfos(int32 ID = -1, TUniquePtr<Y_SubClassIF<class Y_Buff>> StoredClass = nullptr) {
		static TMap<int32, TUniquePtr<Y_SubClassIF<class Y_Buff>>> Cardclass;
		if (ID > 0) {
			Cardclass.Add(ID, MoveTemp(StoredClass));
		}
		return Cardclass;
	};

	template<typename T>
	static TSharedPtr<T> getRandom(TArray<TSharedPtr<T>>& randomArray) {
		float tot = 0;
		TArray<float> pWeights;
		for (auto&& p : randomArray)
		{
			int TW = p->GetWeight();
			tot += TW;
			pWeights.Add(TW);
		}
		float choosed = getRandom() * tot;
		for (int i = 0; i < randomArray.Num();i++) {
			if (choosed < pWeights[i]) return randomArray[i];
			choosed -= pWeights[i];
		}
		return randomArray[0];
	}
};

