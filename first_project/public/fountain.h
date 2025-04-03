// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "first_project.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/Actor.h"
#include "fountain.generated.h"

UCLASS()
class FIRST_PROJECT_API Afountain : public AActor // 언리얼 오브젝트임을 선언, 접두사 A는 엑터 U는 엑터 제외를 의미
{
	GENERATED_BODY() // 

	UPROPERTY(VisibleAnywhere) 
	URotatingMovementComponent* Movement;
	
public:	
	// Sets default values for this actor's properties
	Afountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// 엑터가 게임에서 퇴장할때 호출하는 함수
	// override로 언리얼 함수 상속 확인
	virtual void PostInitializeComponents() override;
	//엑터 셋팅 완료 후 호출 함수

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere) // 메모리 관리를 위해 꼭 넣기! Visible은 속성 편집 가능하게 변경해줌
	UStaticMeshComponent *Body;
	// 메모리를 동적으로 할당해 대입. 메모리 관리에 문제가 발생하지 않음
	UPROPERTY(VisibleAnywhere) // 메모리 관리를 위해 꼭 넣기!
	UStaticMeshComponent *Water;
	// 메모리를 동적으로 할당해 대입. 메모리 관리에 문제가 발생하지 않음

	
	UPROPERTY(VisibleAnywhere) 
	UPointLightComponent *Light;
	UPROPERTY(VisibleAnywhere) 
	UParticleSystemComponent *Splash;

	UPROPERTY(EditAnywhere, Category=ID) // visible은 다른 객체로 변경 불가, 객체에 속한 속성만 변경 가능 (ex staticmesh -> other) edit의 경우 속성의 데이터까지 변경 가능 
	int32 ID; // ID라는 이름을 가진 정수 유형의 맴버 변수 추가 0이 디폴트

private:
	UPROPERTY(EditAnywhere, Category=Stat, Meta = (AllowPrivateAccess = true))
	float RotateSpeed;
};
