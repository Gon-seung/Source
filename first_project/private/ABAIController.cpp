// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AABAIController::HomePosKey(TEXT("HomePos"));
const FName AABAIController::PatrolPosKey(TEXT("PatrolPos"));

AABAIController::AABAIController()
{
    RepeatInterval = 3.0f;
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/BB_ABCharacter")); 
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/BT_ABCharacter")); 
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AABAIController::OnPossess(APawn * InPawn)
{
    Super::OnPossess(InPawn);
    UBlackboardComponent* BlackboardComp = Blackboard.Get();
    this->Blackboard = BlackboardComp;
    if (UseBlackboard(BBAsset, BlackboardComp))
    {
        Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
        if (!RunBehaviorTree(BTAsset))
        {
            ABLOG(Error, TEXT("couldn't run behavior Tree!"))
        }
        //GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &AABAIController::OnRepeatTimer, RepeatInterval, true);
    }
}

void AABAIController::OnUnPossess()
{
    Super::OnUnPossess();
    GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void AABAIController::OnRepeatTimer()
{
    auto CurrentPawn = GetPawn();
    ABCHECK(nullptr != CurrentPawn);

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
    if (nullptr == NavSystem) return;

    FNavLocation NextLocation;
    if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
    {
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
        ABLOG(Warning, TEXT("Next Location: %s"), *NextLocation.Location.ToString());
    }
}
