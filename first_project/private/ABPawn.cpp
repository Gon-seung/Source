// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPawn.h"

// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE")); // 컴포넌트 생성하는 용도
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT")); 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = Capsule; // 대표 컴포넌트 지정
	Mesh->SetupAttachment(Capsule); // 자식이 되도록 선언
	SpringArm->SetupAttachment(Capsule); // 자식이 되도록 선언
	Camera->SetupAttachment(SpringArm); // 자식이 되도록 선언

	Capsule->SetCapsuleHalfHeight(88.0f); 
	Capsule->SetCapsuleRadius(34.0f); 
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f)); 
	SpringArm->TargetArmLength = 400.0f; 
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f)); 
	Camera->SetRelativeLocation(FVector(-200.0f, 0.0f, 0.0f)); // 기본 위치 값 설정

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/ParagonPhase/Characters/Heroes/Phase/Meshes/Phase_GDC.Phase_GDC")); //에셋 불러오는 기능
	if (SK_CARDBOARD.Succeeded())
	{
		ABLOG(Warning, TEXT("Find USkeletalMesh"));
		Mesh->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/ParagonPhase/Characters/Heroes/Phase/Animations/NewAnimBlueprint"));
	if (WARRIOR_ANIM.Succeeded())
	{
		ABLOG(Warning, TEXT("Find AnimationBlueprint"));
		Mesh->SetAnimInstanceClass(WARRIOR_ANIM.Class); // 에니메이션 블루프린트를 연결해서 실행
	}


}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	//Mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	//UAnimationAsset* AnimAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/ParagonPhase/Characters/Heroes/Phase/Animations/Jog_Fwd.Jog_Fwd"));
	//if (AnimAsset != nullptr)
	//{
	//	Mesh->PlayAnimation(AnimAsset, true); // 에니메이션 시퀀스를 연결해서 실행
	//}

}

// Called every frame
void AABPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABPawn::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    ABLOG_S(Warning);
}


void AABPawn::PossessedBy(AController* NewController)
{
    ABLOG_S(Warning);
    Super::PossessedBy(NewController);
}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABPawn::LeftRight);

}

void AABPawn::UpDown(float NewAxisValue)
{
	//ABLOG(Warning, TEXT("%f"), NewAxisValue); // 로그 쌓기기
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void AABPawn::LeftRight(float NewAxisValue)
{
	//ABLOG(Warning, TEXT("%f"), NewAxisValue); // 로그 쌓기기
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}