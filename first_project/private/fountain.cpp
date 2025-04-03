// Fill out your copyright notice in the Description page of Project Settings.


#include "fountain.h"

// Sets default values
Afountain::Afountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // tick 함수 안사용할거면 false, 사용할거면 true
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY")); // 컴포넌트 생성하는 용도
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WATER"));
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT")); 
	Splash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPLASH"));
	Movement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("MOVEMENT"));

	RootComponent = Body; // 대표 컴포넌트 지정
	Water->SetupAttachment(Body); // 자식이 되도록 선언
	Light->SetupAttachment(Body); // 자식이 되도록 선언
	Splash->SetupAttachment(Body); // 자식이 되도록 선언

	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 135.0f)); // 기본 위치 값 설정
	Light->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f)); // 기본 위치 값 설정
	Splash->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f)); // 기본 위치 값 설정

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BODY(TEXT("/Game/StarterContent/Architecture/Wall_Door_400x400.Wall_Door_400x400")); //에셋 불러오는 기능

	if (SM_BODY.Succeeded())
	{
		Body->SetStaticMesh(SM_BODY.Object);
	}

	RotateSpeed = 30.0f;
	Movement->RotationRate = FRotator(0.0f, RotateSpeed, 0.0f);
}

// Called when the game starts or when spawned
void Afountain::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(first_project, Warning, TEXT("Actor Name: %s, ID: %d, Location X: %.3f"), *GetName(), ID, GetActorLocation().X)
	// 시작시 위치에 대한 로그 나오게 하기, 아래 함수로 대체

	ABLOG_S(Warning);
	ABLOG(Warning, TEXT("Actor Name: %s, ID: %d, Location X: %.3f"), *GetName(), ID, GetActorLocation().X)
}

// Called every frame
void Afountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.0f, RotateSpeed * DeltaTime, 0.0f)); // 매 틱마다 일정 속도로 회전

}

void Afountain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason); // 끝나는 시점의 이벤트
	ABLOG_S(Warning);
}

void Afountain::PostInitializeComponents()
{
	Super::PostInitializeComponents(); // 엑터 설계 후 이벤트
	ABLOG_S(Warning);
}