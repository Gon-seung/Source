// Fill out your copyright notice in the Description page of Project Settings.


#include "fountain.h"

// Sets default values
Afountain::Afountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Afountain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Afountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

