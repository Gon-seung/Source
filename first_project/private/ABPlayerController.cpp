// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerController.h"


void AABPlayerController::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    ABLOG_S(Warning);
}


void AABPlayerController::OnPossess(APawn* aPawn)
{
    ABLOG_S(Warning);
    Super::OnPossess(aPawn);
}

void AABPlayerController::BeginPlay()
{
    Super::BeginPlay();
    FInputModeGameOnly InputMode;
    SetInputMode(InputMode); // 마우스클릭 없이 바로 input 홤녀으로 들어감
}
