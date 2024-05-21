// Fill out your copyright notice in the Description page of Project Settings.



#include "PawnController.h"
#include "C:\Program Files\Epic Games\UE_5.2\Engine\Plugins\EnhancedInput\Source\EnhancedInput\Public\InputAction.h"
#include "C:\Program Files\Epic Games\UE_5.2\Engine\Plugins\EnhancedInput\Source\EnhancedInput\Public\InputMappingContext.h"

//static void MapKeys(UInputMappingContext* InputMappingContext, UInputAction* InputAction, FKey Key, bool bNegate = false
//	, bool bSwizzle = false, EInputAxisSwizzle SwizzeleOrder = EInputAxisSwizzle::YXZ)
//{
//
//	auto& Mapping = InputMappingContext->MapKey(InputAction, Key);
//	auto* Outer = InputMappingContext->GetOuter();
//	if (bNegate)
//	{
//		auto* Negate = NewObject<UInputModifierNegate>(Outer);
//		Mapping.Modifiers.Add(Negate);
//	}
//	if (bSwizzle)
//	{
//		auto* Swizzle = NewObject<UInputModifierSwizzleAxis>(Outer);
//		Swizzle->Order = SwizzeleOrder;
//		Mapping.Modifiers.Add(Swizzle);
//	}
//}

APawnController::APawnController() {

	//static ConstructorHelpers::FObjectFinder<UDataTable> DataTableObject(TEXT("DataTable'/Game/BluePrints/PawnDataTable.PawnDataTable'"));
	//if (DataTableObject.Succeeded())
	//{
	//	auto MyDataTable = DataTableObject.Object;

	//	// Iterate over each row in the data table
	//	for (auto RowIt = MyDataTable->GetRowIterator(); RowIt; ++RowIt)
	//	{
	//		// Get the current row data
	//		const FPawnAttributesStruct* DataRow = static_cast<FPawnAttributesStruct*>(RowIt->Value);

	//		// Access and print row data
	//		UE_LOG(LogTemp, Warning, TEXT("Row Name: %s, Value: %d"), *RowIt.Key().ToString(), DataRow->Value);
	//	}
	//}
}
//void APawnController::SetupInputComponent()
//{
//	Super::SetupInputComponent();
//	PawnMappingContext = NewObject<UInputMappingContext>(this);
//	MoveAction = NewObject<UInputAction>(this);
//	MoveAction->ValueType = EInputActionValueType::Axis3D;
//
//
//	// Mapping  For W for forward
//	//PawnMappingContext->MapKey(MoveAction,EKeys::W);
//
//
//	//// Mapping for S for back
//	//auto& Mapping = PawnMappingContext->MapKey(MoveAction, EKeys::S);
//	//auto* Negate = NewObject<UInputModifierNegate>(this);
//	//Mapping.Modifiers.Add(Negate);
//
//	// for move forward
//	MapKeys(PawnMappingContext, MoveAction, EKeys::W);
//	MapKeys(PawnMappingContext, MoveAction, EKeys::S, true);
//	MapKeys(PawnMappingContext, MoveAction, EKeys::A, true, true);
//	MapKeys(PawnMappingContext, MoveAction, EKeys::D, false, true);
//	MapKeys(PawnMappingContext, MoveAction, EKeys::E, false, true, EInputAxisSwizzle::ZYX);
//	MapKeys(PawnMappingContext, MoveAction, EKeys::Q, true, true, EInputAxisSwizzle::ZYX);
//
//	RotateAction = NewObject<UInputAction>(this);
//	RotateAction->ValueType = EInputActionValueType::Axis2D;
//
//	MapKeys(PawnMappingContext, RotateAction, EKeys::MouseY);
//	MapKeys(PawnMappingContext, RotateAction, EKeys::MouseX,false,true);
//
//}

