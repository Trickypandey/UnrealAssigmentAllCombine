// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "PerspectiveView.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class ASSIGMENT3_4_API APerspectiveView : public APawn
{
	GENERATED_BODY()

public:
	void KeyMap(::UInputMappingContext* InputMappingContext, const ::UInputAction* InputAction, const FKey& Key,
	            bool bNegate, bool bSwizzle, EInputAxisSwizzle SwizzleOrder);
	// Sets default values for this pawn's properties
	APerspectiveView();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	class UInputMappingContext* PawnMappingContext;

	UPROPERTY()
	class UInputAction* MoveAction;

	UPROPERTY()
	UInputAction* RotateAction;

	float RotateScale;

	void Move(const struct FInputActionValue& ActionValue);
	void Rotate(const FInputActionValue& ActionValue);

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY()
	class UFloatingPawnMovement* PMovement;

};
