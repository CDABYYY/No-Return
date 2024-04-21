// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template <typename T>
class DEMO0_API YOArray
{
    template <typename T1>
    class CustomSorterIF
    {
    public:
        virtual bool Cmp(T1& a1, T1& a2) = 0;
        virtual ~CustomSorterIF() {};
    };
    template <typename T2, typename F>
    class CustomSorter : public CustomSorterIF<T2>
    {
    public:
        F Function;
        CustomSorter(F f) : Function(f) {};
        virtual bool Cmp(T2& a1, T2& a2) override
        {
            return Function(a1, a2);
        }
    };
public:
	TArray<T> Data;
    TUniquePtr<CustomSorterIF<T>> Sorter;

    template <typename F2>
    void reset(F2 f2) {
        Sorter = TUniquePtr<CustomSorterIF<T>>(new CustomSorter<T, F2>(f2));
        //Data.Sort(Sorter.Get()->Cmp);
    }

	YOArray(){};

    template <typename F2>
    YOArray(F2 f2) {
        reset(f2);
    }

    void Add(T t)
    {
        auto pos = 0;
        for (; pos < Data.Num(); pos++)
        {
            if (!Sorter.Get()->Cmp(Data[pos], t))
                break;
        }
        Data.Insert(t, pos);
    };
    auto begin() -> decltype(Data.begin())
    {
        return Data.begin();
    };
    auto end() -> decltype(Data.end())
    {
        return Data.end();
    }
    void RemoveAt(int32 i) {
        Data.RemoveAt(i);
    }

    void RemoveFirst(T& t)
    {
        Data.RemoveSingle(t);
        //for (int32 i = 0; i < Data.Num(); i++)
        //{
        //    if (Data[i] == t)
        //    {
        //        Data.RemoveAt(i);
        //        break;
        //    }
        //}
    }
    void RemoveAll(T& t) {
        Data.Remove(t);
    }
    int32 Num() {
        return Data.Num();
    }
    int32 Find(T& t) {
        int32 b = 0, e = Data.Num();
        while (b < e) {
            int32 t0 = (b + e) / 2;
            if (Sorter.Get()->Cmp(Data[t0], t)) b = t0 + 1;
            else e = t0;
        }
        if (Data[b] == t)return b;
        else return -1;
    }
};
