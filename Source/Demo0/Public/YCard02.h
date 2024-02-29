// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_Card.h"
#include "YCard02.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API AYCard02 : public AY_Card
{
	GENERATED_BODY()
	AYCard02();
	virtual void Play() override;
	virtual void Clicked() override;
	virtual bool AcceptFloor(class AY_Floor*) override;
};
