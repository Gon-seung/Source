// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h" 
// "#include "CoreMinimal.h"
// 콘텐츠 제작 시에 다양한 엔진 기능이 필요하기에 EngineMinimal.h 파일을 사용 
// "CoreMinimal.h"은 최소 기능만 선언

DECLARE_LOG_CATEGORY_EXTERN(first_project, Log, All);
#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define ABLOG_S(Verbosity) UE_LOG(first_project, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
#define ABLOG(Verbosity, Format, ...) UE_LOG(first_project, Verbosity, TEXT("%s%s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define ABCHECK(Expr, ...) {if(!(Expr)) {ABLOG(Error, TEXT("ASSERTION: %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}} 
// 런타임 문제시 에러 
