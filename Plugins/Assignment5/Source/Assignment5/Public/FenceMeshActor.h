// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VerticalRailActor.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FenceMeshActor.generated.h"

USTRUCT(BlueprintType)
struct FFenceProperties
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence Properties")
    float Length;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence Properties")
    float Width;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence Properties")
    float Height;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence Properties")
    float Spacing;
};

UCLASS()
class ASSIGNMENT5_API AFenceMeshActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AFenceMeshActor();

protected:  
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

private:
    void ClearPreviousAttachedMesh();
    void CreateHorizontalFence(const FVector& StartPos, const FVector& EndPos);

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USceneComponent* SceneComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USplineComponent* Spline;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence", meta = (AllowPrivateAccess = "true"))
    UStaticMesh* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence", meta = (AllowPrivateAccess = "true"))
    UMaterialInterface* FenceMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence", meta = (AllowPrivateAccess = "true"))
    UStaticMesh* HorizontalFenceStaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence", meta = (AllowPrivateAccess = "true"))
    FFenceProperties FenceProperties;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AVerticalRailActor> PillarActorClass;


    UPROPERTY()
    TArray<UStaticMeshComponent*> SplineMeshes;
    UPROPERTY()
    TArray<AVerticalRailActor*> SpawnedPillars;
};
