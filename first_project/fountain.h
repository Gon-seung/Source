// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "fountain.generated.h"

UCLASS()
class FIRST_PROJECT_API Afountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Afountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
