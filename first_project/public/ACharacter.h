// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "first_project.h" // 변경
#include "GameFramework/Character.h"
#include "ACharacter.generated.h"

UCLASS()
class FIRST_PROJECT_API AACharacter : public ACharacter 
// ACharacter로부터 상속받는데, 해당 크래스는 APawn 클래스를 상속받고 있음
// 동일한 Capsule 컴포넌트 SkeletalMesh 컴포넌트, CharacterMovement 컴포넌트 사용 사용
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum class EControlMode
	{
		GTA,
		DIABLO
	};

	void SetControlMode(EControlMode NewControlMode); // GTA 카메라 모드 설정
	EControlMode CurrentControlMode = EControlMode::GTA;
	FVector DirectionToMove = FVector::ZeroVector; // 변수들은 초기 값 미리 지정이 안전

	//float ArmLengthTo = 0.0f;
	//FRotator ArmRotationTo = FRotator::ZeroRotator;
	//float ArmLengthSpeed = 0.0f;
	//float ArmRotationSpeed = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser	
	) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category=Stat) 
	class UABCharacterStatComponent* CharacterStat;
	
	UPROPERTY(VisibleAnywhere, Category=Camera) 
	USpringArmComponent *SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category=Camera) 
	UCameraComponent *Camera;

	UPROPERTY(VisibleAnywhere, Category=UI) 
	class UWidgetComponent* HPBarWidget;

	UPROPERTY(
		VisibleInstanceOnly, 
		BlueprintReadOnly,
		Category = Attack,
		Meta = (AllowPrivateAccess = true))
	float AttackRange;

	UPROPERTY(
		VisibleInstanceOnly, 
		BlueprintReadOnly,
		Category = Attack,
		Meta = (AllowPrivateAccess = true))
	float AttackRadius;

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	void ViewChange();
	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(VisibleInstanceOnly,
		BlueprintReadOnly, // 오로지 값을 읽기만 함, 쓰는건 BlueprintReadWrite
		Category=Attack, 
		Meta=(AllowPrivateAccess=true)
	)
	bool IsAttacking;

	UPROPERTY()
	class UABAnimInstance* ABAnim;
	
	void AttackCheck();
};
