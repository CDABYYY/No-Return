// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_AnimInstance.h"
#include "Y_Character.h"

void UY_AnimInstance::NativeInitializeAnimation() {
	if (!Owner) {
		Owner = Cast<AY_Character>(TryGetPawnOwner());
	}
}

void UY_AnimInstance::UpdateAnimationPropertiers() {
	if (!Owner) {
		Owner = Cast<AY_Character>(TryGetPawnOwner());
	}

	if (Owner) {
		Status = Owner->CharacterStatus = 1;
	}
}
