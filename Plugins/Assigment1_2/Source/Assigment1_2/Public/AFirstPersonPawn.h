// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "InputModifiers.h"
#include "../Public/BaseCharacter.h"
#include "AFirstPersonPawn.generated.h"

UCLASS()
class ASSIGMENT1_2_API AAFirstPersonPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAFirstPersonPawn();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	UPROPERTY()
	class UInputMappingContext* PawnMappingContext;

	UPROPERTY()
	class UInputAction* MoveAction;


	UPROPERTY()
	UInputAction* RotateAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	//void MoveRight(float Value);
	void LookUp(float Value);
	void LookRight(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to inpu
	void Move(const struct FInputActionValue& ActionValue);
	void Rotate(const struct FInputActionValue& ActionValue);

	UPROPERTY()
	class UFloatingPawnMovement* pMovement;

	UPROPERTY(EditAnywhere)
	float MoveScale;
	
	UPROPERTY(EditAnywhere)
	float RotateScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPawnAttributeAsset* PawnAttributes;


private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

};
