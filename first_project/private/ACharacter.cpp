// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharacter.h"
#include "ABAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "ABCharacterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "ABCharacterWidget.h"
#include "ABAIController.h"

// Sets default values
AACharacter::AACharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CharacterStat = CreateDefaultSubobject<UABCharacterStatComponent>(TEXT("CHARACTERSTAT"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));


	SpringArm->SetupAttachment(GetCapsuleComponent()); // 자식이 되도록 선언
	Camera->SetupAttachment(SpringArm); // 자식이 되도록 선언
	HPBarWidget->SetupAttachment(GetMesh()); 

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f)); 
	SpringArm->TargetArmLength = 400.0f; 
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f)); 
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f)); 
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen); 
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/UI/UI_HPBAR"));
	if (UI_HUD.Succeeded())
	{
		ABLOG(Warning, TEXT("Find HPBarWidget"));
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}


	//Camera->SetRelativeLocation(FVector(-200.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/ParagonPhase/Characters/Heroes/Phase/Meshes/Phase_GDC.Phase_GDC")); //에셋 불러오는 기능
	if (SK_CARDBOARD.Succeeded())
	{
		ABLOG(Warning, TEXT("Find USkeletalMesh"));
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/ParagonPhase/Characters/Heroes/Phase/Animations/NewAnimBlueprint"));
	if (WARRIOR_ANIM.Succeeded())
	{
		ABLOG(Warning, TEXT("Find AnimationBlueprint"));
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class); // 에니메이션 블루프린트를 연결해서 실행
	}

	SetControlMode(EControlMode::DIABLO); // 0번 모드는  gTA방식 3인칭 조작

	//ArmLengthSpeed = 3.0f;
	//ArmRotationSpeed = 10.0f;
	GetCharacterMovement()->JumpZVelocity = 800.0f; // jump 값 할당

	IsAttacking = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ACharacter")); // 충돌 프로필 이름 설정

	AttackRange = 200.0f;
	AttackRadius = 50.0f;

	AIControllerClass = AABAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AACharacter::BeginPlay()
{
	Super::BeginPlay();
	
	auto CharacterWidget = Cast<UABCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget){
		CharacterWidget->BindCharacterStat(CharacterStat);
	}
}

// Called every frame
void AACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);
	switch(CurrentControlMode) {
		case EControlMode::DIABLO:
			SpringArm->RelativeRotation = FMath::RInterpTo(SpringArm->RelativeRotation, ArmRotationTo, DeltaTime, ArmRotationSpeed);
			// 부드럽게 바꾸기
			break;
	}
	*/
	switch (CurrentControlMode)
	{
		case EControlMode::DIABLO:
			if (DirectionToMove.SizeSquared() > 0.0f)
			{
				GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
				AddMovementInput(DirectionToMove);
			}
			break;
	}

}

// Called to bind functionality to input
void AACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("ViewChange"), 
									EInputEvent::IE_Pressed,
									this,
									&AACharacter::ViewChange);
	PlayerInputComponent->BindAction(TEXT("Jump"), 
									EInputEvent::IE_Pressed,
									this,
									&AACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("ATTACK"), 
									EInputEvent::IE_Pressed,
									this,
									&AACharacter::Attack);
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AACharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AACharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AACharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AACharacter::Turn);
	
}

void AACharacter::Attack()
{
	if (IsAttacking) return;
	//auto AnimInstance = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	//if (nullptr == AnimInstance) return;
	// 밑에 ABAnim으로 대체
	ABLOG_S(Warning);
	ABAnim->PlayAttackMontage();
	IsAttacking = true;


}

void AACharacter::ViewChange()
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		//GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);
		break;
	case EControlMode::DIABLO:
		//GetController()->SetControlRotation(SpringArm->RelativeRotation);
		SetControlMode(EControlMode::GTA);
		break;
	}

}

void AACharacter::UpDown(float NewAxisValue)
{
	//ABLOG(Warning, TEXT("%f"), NewAxisValue); // 로그 쌓기기
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(
			FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f))
				.GetUnitAxis(EAxis::X), 
			NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.X = NewAxisValue;
		break;
	}
	/*
	AddMovementInput(
		//GetActorForwardVector(),  // 단순 앞
		FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), // 카메라 방향으로 이동
		NewAxisValue
	);
	*/
}

void AACharacter::LeftRight(float NewAxisValue)
{
	//ABLOG(Warning, TEXT("%f"), NewAxisValue); // 로그 쌓기기
	//ABLOG(Warning, TEXT("%f"), NewAxisValue); // 로그 쌓기기
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(
			FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f))
				.GetUnitAxis(EAxis::Y), 
			NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.Y = NewAxisValue;
		break;
	}
}

void AACharacter::LookUp(float NewAxisValue)
{
	// 회전 관련 종류: AddControllerInputYaw Roll Pitch
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerPitchInput(NewAxisValue);
		break;
	}
}

void AACharacter::Turn(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerYawInput(NewAxisValue);
		break;
	}
}

void AACharacter::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		SpringArm->TargetArmLength = 450.0f;
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		//ArmLengthTo = 450.0f;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true; // 카메라 방향으로 캐릭터 몸을 보도록 변경
		GetCharacterMovement()->bUseControllerDesiredRotation = false; // 캐릭터가 부드럽게 회전
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // 카메라 방향으로 캐릭터 몸을 보도록 변경
		break;
	case EControlMode::DIABLO:
		SpringArm->TargetArmLength = 800.0f;
		SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		//ArmLengthTo = 800.0f;
		//ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false; // 카메라 방향으로 캐릭터 몸을 보도록 변경
		GetCharacterMovement()->bUseControllerDesiredRotation = true; // 캐릭터가 부드럽게 회전
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // 카메라 방향으로 캐릭터 몸을 보도록 변경
		break;

	}
}

void AACharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//auto AnimInstance = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	//ABCHECK(nullptr != AnimInstance);
	//AnimInstance->OnMontageEnded.AddDynamic(this, &AACharacter::OnAttackMontageEnded);
	// 밑의 클래스 호출을 통한 방식으로 변경

	ABAnim = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	ABCHECK(nullptr != ABAnim);
	ABAnim->OnMontageEnded.AddDynamic(this, &AACharacter::OnAttackMontageEnded);
	
	ABAnim->OnAttackHitCheck.AddUObject(this, &AACharacter::AttackCheck); //  trace 체크를 통한 충돌 설정
	
	CharacterStat->OnHPIsZero.AddLambda([this]()-> void{
		ABLOG(Warning, TEXT("OnHPIsZero"));
		ABAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	});

}

void AACharacter::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	ABCHECK(IsAttacking);
	IsAttacking = false;
}

void AACharacter::AttackCheck() // attack 체크후 충돌 설정
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

#if ENABLE_DRAW_DEBUG // 영역을 red와 green으로 설정
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(
		GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime
	);
#endif

	if (bResult){
		if (::IsValid(HitResult.GetActor())) // 5버전 이상은 Actor -> GetActor로 // HitResult.Actor.IsValid() -> HitResult.GetActor()
		{
			ABLOG(Warning, TEXT("Hit Actor Name: %s"), *HitResult.GetActor()->GetName());
			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);
		}
	}
}

float AACharacter::TakeDamage(
	float DamageAmount,
	FDamageEvent const & DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser) // attack 체크후 충돌 설정
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ABLOG(Warning, TEXT("Actor: %s took Damage: %f"), *GetName(), FinalDamage);
	CharacterStat->SetDamage(FinalDamage);
	//if (FinalDamage > 0.0f)
	//{
	//	ABAnim -> SetDeadAnim();
	//	SetActorEnableCollision(false);
	//}
	return FinalDamage;
}