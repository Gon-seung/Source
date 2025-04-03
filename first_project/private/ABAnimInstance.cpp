// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"


UABAnimInstance::UABAnimInstance()
{
    CurrentPawnSpeed = 0.0f;
    IsInAir = false;
    IsDead = false;


	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/ParagonPhase/Characters/Heroes/Phase/Animations/SK_phase_Skeleton_Montage")); //에셋 불러오는 기능
	if (ATTACK_MONTAGE.Succeeded())
	{
		ABLOG(Warning, TEXT("Find MONTAGE"));
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UABAnimInstance::PlayAttackMontage()
{

    Montage_Play(AttackMontage, 1.0f);
    //if (!Montage_IsPlaying(AttackMontage))
    // 시작 확인은 character에서 가능

}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    auto Pawn = TryGetPawnOwner(); // 폰 오브젝트의 포인터 받아오기
    if(!::IsValid(Pawn)) return;

    if (!IsDead)
    {
        CurrentPawnSpeed = Pawn->GetVelocity().Size(); // 속도 값 받아오기
        auto Character = Cast<ACharacter>(Pawn);
        if (Character)
        {
            IsInAir = Character->GetMovementComponent()->IsFalling();
        }
    }

}

void UABAnimInstance::AnimNotify_AttackHitCheck()
{
    ABLOG_S(Warning);
    ABCHECK(!IsDead);
    OnAttackHitCheck.Broadcast();
}

void UABAnimInstance::AnimNotify_NextAttackHitCheck()
{
    ABLOG_S(Warning);
    ABCHECK(!IsDead);
    OnNextAttackCheck.Broadcast();
}

