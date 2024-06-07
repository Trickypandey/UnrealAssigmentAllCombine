// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ScatterDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ASSIGNMENT6_API UScatterDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter")
	TArray<UStaticMesh*> StaticMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter")
	float MinScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter")
	float MaxScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter")
	float MinRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter")
	float MaxRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter")
	float MinDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter")
	float MaxDistance;

};
