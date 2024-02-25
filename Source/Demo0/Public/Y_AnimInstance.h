// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Y_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Status;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class AY_Character* Owner;

	UFUNCTION(BlueprintCallable, Category = AnimationProperty)
	void UpdateAnimationPropertiers();

	virtual void NativeInitializeAnimation()override;
};
