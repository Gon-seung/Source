// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "first_project.h" // 변경
#include "GameFramework/PlayerController.h"
#include "ABPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_PROJECT_API AABPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void PostInitializeComponents() override;
	// 로그인 후 컨트롤러 생성
	virtual void OnPossess(APawn* aPawn) override;
	// 로그인 후 컨트롤러 생성

protected:
	virtual void BeginPlay() override;
};
