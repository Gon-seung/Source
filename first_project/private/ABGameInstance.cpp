// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
    FString CharacterDataPath = TEXT("/Game/ABCharacter");
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABCHARACTER(*CharacterDataPath);
    ABCHECK(DT_ABCHARACTER.Succeeded());
    ABCharacterTable = DT_ABCHARACTER.Object;
    //ABCHECK(DT_ABCHARACTER->GetRowMap().Num() > 0);
}

void UABGameInstance::Init()
{
    Super::Init();
    ABLOG_S(Warning);
    ABLOG(Warning, TEXT("DropExp of Level 20 ABCharacter : %d"), GetABCharacterData(20)->DropExp);

}


FABCharacterData* UABGameInstance::GetABCharacterData(int32 Level){
    return ABCharacterTable->FindRow<FABCharacterData>(*FString::FromInt(Level), TEXT(""));
}
