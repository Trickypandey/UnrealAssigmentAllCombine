// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FPawnAttributesStruct.generated.h"

/**
 * 
 */
UENUM()
enum class EPawnType : int8 {
	FirstPerson,
	ThirdPerson,
	TopDown
};


USTRUCT(Blueprintable)
struct FPawnAttributesStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	EPawnType CharacterType{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Reference")
	TSubclassOf<APawn> PawnClass{};
};