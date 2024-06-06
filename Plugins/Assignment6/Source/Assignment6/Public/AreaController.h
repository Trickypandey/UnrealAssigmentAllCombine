// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectionArea.h"
#include "GameFramework/PlayerController.h"
#include "AreaController.generated.h"

class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class ASSIGNMENT6_API AAreaController : public APlayerController
{
	GENERATED_BODY()

public:
	AAreaController();

	virtual void SetupInputComponent() override;
	void SetupEnhancedInputBindings();

	UPROPERTY()
	UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Controller")
	UInputAction* OnMouseHover;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ASelectionArea* CurrentActor;

	UFUNCTION()
	void ChangeLocation();

	virtual void Tick(float DeltaSeconds) override;  

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ASelectionArea> SelectionAreaClass;


	
};
