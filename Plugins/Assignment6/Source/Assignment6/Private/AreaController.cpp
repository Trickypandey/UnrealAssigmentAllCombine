// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaController.h"
#include "InputMappingContext.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SelectionArea.h"


AAreaController::AAreaController()
{
    PrimaryActorTick.bCanEverTick = true;
    bShowMouseCursor = true;
    //SelectionAreaClass = ASelectionArea::StaticClass();
}

void AAreaController::SetupInputComponent()
{
    Super::SetupInputComponent();
    SetupEnhancedInputBindings();
}

void AAreaController::SetupEnhancedInputBindings()
{
    UEnhancedInputComponent* Eic = Cast<UEnhancedInputComponent>(InputComponent);
    MappingContext = NewObject<UInputMappingContext>(this);

    OnMouseHover = NewObject<UInputAction>(this);
    OnMouseHover->ValueType = EInputActionValueType::Boolean;


    check(Eic)
        Eic->BindAction(OnMouseHover, ETriggerEvent::Started, this, &AAreaController::ChangeLocation);

    if (MappingContext) {
        MappingContext->MapKey(OnMouseHover, EKeys::LeftMouseButton);

    }

    auto* SubSystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    if (SubSystem)

    {
        SubSystem->AddMappingContext(MappingContext, 0);
    }
}

void AAreaController::ChangeLocation()
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECC_Visibility, true, HitResult);
    if (HitResult.bBlockingHit)
    {
        FVector ClickLocation = HitResult.Location;

        if (ASelectionArea* ArchActor = Cast<ASelectionArea>(HitResult.GetActor())) {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Clicked Location: X=%f, Y=%f, Z=%f"), ClickLocation.X, ClickLocation.Y, ClickLocation.Z));
            CurrentActor = ArchActor;
            return;
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Not An Actor: X=%f, Y=%f, Z=%f"), ClickLocation.X, ClickLocation.Y, ClickLocation.Z));
            CurrentActor = nullptr;

        }

        if (CurrentActor)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("in curretn actor : X=%f, Y=%f, Z=%f"), ClickLocation.X, ClickLocation.Y, ClickLocation.Z));
            //CurrentActor->SetActorLocation(ClickLocation);
        }
        

    }
}

void AAreaController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CurrentActor)
	{
	    FVector WorldLocation, WorldDirection;
	    DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	    FVector NewLocation = WorldLocation + WorldDirection * 600.0f;
        NewLocation += FVector(10);
	    CurrentActor->SetActorRelativeLocation(NewLocation);
		
	}

}

void AAreaController::BeginPlay()
{
	Super::BeginPlay();
    if (SelectionAreaClass)
    {
        FVector SpawnLocationActor = FVector(0.f, 0.f, 100.f); // Adjust Z value to make sure it's above the floor
        FRotator SpawnRotation = FRotator::ZeroRotator;
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetPawn();

        CurrentActor = GetWorld()->SpawnActor<ASelectionArea>(SelectionAreaClass, SpawnLocationActor, SpawnRotation, SpawnParams);

        if (CurrentActor)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Spawned SelectionArea Actor"));
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to Spawn SelectionArea Actor"));
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("SelectionAreaClass is not set"));
    }

}

