// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "first_project.h" // 변경
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "ABGameInstance.generated.h"


USTRUCT(BlueprintType)
struct FABCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FABCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
	
};


UCLASS()
class FIRST_PROJECT_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UABGameInstance();

	virtual void Init() override;
	FABCharacterData* GetABCharacterData(int32 Level);

private:
	UPROPERTY()
	class UDataTable* ABCharacterTable;

};
