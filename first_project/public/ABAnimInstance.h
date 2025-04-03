// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "first_project.h" // 변경
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class FIRST_PROJECT_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UABAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage();

	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	void SetDeadAnim() {IsDead = true;}

private:
	UPROPERTY(EditAnywhere, 
		BlueprintReadOnly, // 오로지 값을 읽기만 함, 쓰는건 BlueprintReadWrite
		Category=Pawn, 
		Meta=(AllowPrivateAccess=true)
	)
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, 
		BlueprintReadOnly, // 오로지 값을 읽기만 함, 쓰는건 BlueprintReadWrite
		Category=Pawn, 
		Meta=(AllowPrivateAccess=true)
	)
	bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDead;
	
	UPROPERTY(VisibleDefaultsOnly, 
		BlueprintReadOnly, // 오로지 값을 읽기만 함, 쓰는건 BlueprintReadWrite
		Category=Attack, 
		Meta=(AllowPrivateAccess=true)
	)
	UAnimMontage* AttackMontage;

	UFUNCTION() //언리얼 런타임이 찾을 수 있도록 반드시 넣어야함
	void AnimNotify_AttackHitCheck();
	void AnimNotify_NextAttackHitCheck();

};
