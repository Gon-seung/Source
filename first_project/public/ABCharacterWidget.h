// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "first_project.h" // 변경
#include "Blueprint/UserWidget.h"
#include "ABCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_PROJECT_API UABCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	void BindCharacterStat(class UABCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UABCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;
};