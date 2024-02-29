// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_Card.h"
#include "YCard01.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API AYCard01 : public AY_Card
{
	GENERATED_BODY()
	AYCard01();
	virtual void Play() override;
	virtual void Clicked() override;
	virtual bool AcceptFloor(class AY_Floor*) override;
};
