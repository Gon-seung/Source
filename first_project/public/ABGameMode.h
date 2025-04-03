// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "first_project.h" // 변경
#include "GameFramework/GameModeBase.h"
#include "ABGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_PROJECT_API AABGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AABGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	// 로그인 후 컨트롤러 생성
	// postlogin 이벤트로 폰 생성 후 폰에 빙의
};
