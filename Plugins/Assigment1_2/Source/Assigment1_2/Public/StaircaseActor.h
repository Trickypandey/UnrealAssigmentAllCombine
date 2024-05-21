// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaircaseActor.generated.h"

UENUM(BlueprintType, category = "Manipulate Staircase")
enum class EtypeOfStairs : uint8 {
    openTypeStairs UMETA(DisplayName = "OpenStairs"),
    closeTypeStairs UMETA(DisplayName = "CloseStairs"),
    boxTypeStairs UMETA(DisplayName = "BoxStairs")
};

UCLASS()
class ASSIGMENT1_2_API AStaircaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStaircaseActor();
	
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staircase Properties")
    int32 NumberOfSteps = 1;

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staircase Properties")
    UStaticMesh* StepMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staircase Properties")
    USceneComponent* StepSceneComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staircase Properties")
    FVector StepDimension = FVector(1.f, 4.f, 0.5f);
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Railing Properties")
    UStaticMesh* RailingMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Railing Properties")
    UStaticMesh* RailingHandleMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Railing Properties")
    float RailingHeight = 50.f;

    UPROPERTY(EditAnywhere, Category = "Change StairCase")
    TEnumAsByte<EtypeOfStairs> TypeOfStair;

    void DestroyAllChildrenComponents();

    /*UStaticMeshComponent* CreateStepComponent(int32 StepIndex);

    void AddRailingsToStep(UStaticMeshComponent* StepComponent, int32 StepIndex);

    UStaticMeshComponent* CreateAndAttachRailingComponent(UStaticMeshComponent* ParentComponent, const FVector& RelativeLocation, float ScaleFactor);*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;
    void CreateStepComponent(int32 StepIndex);
    void CreateRailing(int32 StepIndex, UStaticMeshComponent* StepComponent);
    void CalculateRailingHandleRotation(UStaticMeshComponent* ComponentToAttach);
    UStaticMeshComponent* CreateRailingComponent(const FString& ComponentName, int32 StepIndex, const FVector& RelativeLocation, UStaticMeshComponent* _StepComponent);

    //virtual void PreEditChange(FProperty* P) override;


};
