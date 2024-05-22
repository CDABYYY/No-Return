// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_MapWidget.h"
#include "Y.h"
#include "Y_RoomWidget.h"
#include "Y_Fighting.h"
#include "Y_ClassBase.h"


TArray<int32> UY_MapWidget::GetWay(int32 a0, int32 b0, int32 f0)
{
	
    int32 af = a0 + b0 - 1; 

    int32 bf = a0;
    if (b0 > a0) bf = b0;

    int32 f = 0; 

    for (int32 i = 0; i < af - bf; i++)
    {
        if (Y::getRandom() < a)
            f++;
    }

    float rate = calculate(a0, f);


    int32 ra = 1, rb = 1;

    int32 rf = 0, sf = 0;

    TArray<int32> result;
    for (; ra < a0; ra++)
    {
        result.Add((f0 << 20) + (ra << 10) + rb);
        if (Y::getRandom() < rate && rf < f)
        {
            rb++;
            rf++;
            result.Add((f0 << 20) + (ra << 10) + rb);
            while (Y::getRandom() < b * rate && rf < f)
            {
                rb++;
                rf++;
                result.Add((f0 << 20) + (ra << 10) + rb);
            }
        }

        if (f < af - bf && Y::getRandom() < (float)(af - bf - f - sf) / (a0 - ra))
        {
            rb++;
            sf++;
        }
    }
    for (; rb <= b0; rb++)
    {
        result.Add((f0 << 20) + (ra << 10) + rb);
    }
    return result;
}

void UY_MapWidget::ForwardRoom(UY_RoomWidget* Room)
{
    Room->RoomStatus = 2;
    int32 p = plevel.Find(Room);
    int32 np = p;
    int32 p0 = p;
    int32 p1 = 0;
    int32 lt = 0;
    for (auto& l : levels) {
        if (p < l) {
            p0 = p0 - p;
            p1 = p0 + l;
            break;
        }
        p -= l;
        lt++;
    }
    Y::GetGameInfo()->CurrentFloor = lt;
    //Default. Need Next Try
    for (auto& w : pway) {
        if ((w >> 10) == ((lt << 10) + p + 1)) {
            plevel[p1 + w % (1 << 10) - 1]->RoomStatus = 0;
            plevel[p1 + w % (1 << 10) - 1]->SetArrivable();
        }
    }
    for (int32 i = p0; i < p1; i++) {
        if(i != np)
        {
            plevel[i]->RoomStatus = 3;
            plevel[i]->Passed();
        }
    }
}

void UY_MapWidget::GetMap()
{
    if(Y::GetGameInfo()->CurrentLevel->MapTexture)
        UsingTexture = Y::GetGameInfo()->CurrentLevel->MapTexture;

    weight.Add(14, 20);
    weight.Add(15, 30);
    weight.Add(16, 20);
    int32 getf = Y::getRandom(weight);

    slevel.Add(3, 10);
    slevel.Add(4, 20);
    slevel.Add(5, 10);
    auto FirstRoom = DrawEvent(1.0f / (getf + 3), 0.5);
    FirstRoom->RoomStatus = 0;
    plevel.Add(FirstRoom);
    levels.Add(1);
    for (int32 i = 0; i < getf; i++)
    {
        int32 getR = Y::getRandom(slevel);
        for (int32 j = 0; j < getR; j++)
        {
            auto NewRoom = DrawEvent((2.0f + i) / (getf + 3), (1.0f + j) / (getR + 1));
            if (Y::getRandom() < 0.5)NewRoom->LoadInfo(MakeShared<NormalFightRoom>());
            plevel.Add(NewRoom);
        }
        levels.Add(getR);
        pway.Append(GetWay(levels[levels.Num() - 2], levels[levels.Num() - 1], i));
    }
    auto LastRoom = DrawEvent((2.0f + getf) / (getf + 3), 0.5);
    LastRoom->LoadInfo(Y::GetGameInfo()->CurrentLevel->FinalRoom);
    plevel.Add(LastRoom);
    levels.Add(1);
    pway.Append(GetWay(levels[levels.Num() - 2], levels[levels.Num() - 1], getf));
}

void UY_MapWidget::DrawWay(FVector2D ParentSize)
{
    TArray<FVector2D> results;
    for (auto i : pway) {
        int32 tb = i % (1 << 10);
        int32 ta = (i >> 10) % (1 << 10);
        int32 tf = i >> 20;
        WayToDraw.Add(FVector2D((1.0f + tf) / (levels.Num() + 1) * ParentSize.X, ((float)ta) / (levels[tf] + 1) * ParentSize.Y));
        WayToDraw.Add(FVector2D((2.0f + tf) / (levels.Num() + 1) * ParentSize.X, ((float)tb) / (levels[tf + 1] + 1) * ParentSize.Y));
    }
}

float UY_MapWidget::calculate(int32 a0, int32 f)
{
    if (Rates.Contains(a0 * 100 + f))
        return *Rates.Find(a0 * 100 + f);

    if (b > 1)
        b = 1 + (b - 1) * (a0 - 1);
    float to = (float)f / a0;
    float be = (float)1 / a0, en = to;
    for (int i = 0; i < 20; i++)
    {
        float t = (be + en) / 2;
        float result = (pow(b, f) * pow(t, f + 1) - t) / (1 - b * t);
        if (result > to)
            be = to;
        else
            en = to;
    }
    Rates.Add(a0 * 100 + f, (be + en) / 2);
    return (be + en) / 2;
}
