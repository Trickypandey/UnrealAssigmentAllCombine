// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VerticalRailActor.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/SceneComponent.h"
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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void AttachMesh(const FVector& Location, const FRotator& Rotation);
	virtual void OnConstruction(const FTransform& Transform) override;
	void AttachCuboidMeshes();
	void ClearPreviousAttachedMesh();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USplineComponent* Spline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence")
	FFenceProperties FenceProperties;

	UPROPERTY()
	TArray<USplineMeshComponent*> MeshComponents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence")
	TSubclassOf<AVerticalRailActor> VerticalRailActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence")
	FVector CuboidDimensions;
private:
	TArray<AActor*> AttachedMeshes;
	//void AttachCuboidMeshes();

};
