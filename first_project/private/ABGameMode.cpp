// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include "ACharacter.h"
#include "ABPlayerController.h"

AABGameMode::AABGameMode()
{
    DefaultPawnClass = AACharacter::StaticClass(); 
    // 멀티를 고려해 클래스 정보만 저장하고 입장할 때마다 클래스를 기반으로 폰 생성성
    PlayerControllerClass = AABPlayerController::StaticClass();

}

void AABGameMode::PostLogin(APlayerController* NewPlayer)
{
    ABLOG(Warning, TEXT("PostLogin Begin"));
    Super::PostLogin(NewPlayer);
    ABLOG(Warning, TEXT("PostLogin END"));
}
