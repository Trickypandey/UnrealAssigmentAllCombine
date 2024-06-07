// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "SelectionArea.generated.h"

UENUM(BlueprintType)
enum class ESelectionAreaType : uint8
{
	Sphere UMETA(DisplayName = "Sphere"),
	Box UMETA(DisplayName = "Box")
};
UCLASS()
class ASSIGNMENT6_API ASelectionArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelectionArea();
	virtual void OnConstruction(const FTransform& Transform) override;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;*/

	UPROPERTY()
	USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMesh* SphereMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMesh* BoxMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UProceduralMeshComponent* ProceduralMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	ESelectionAreaType SelectionAreaType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UMaterial* Material;

	UFUNCTION(BlueprintCallable,Category = "Mesh")
	void ToggleShape();

	bool bIsSphere;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Selection Area")
	void UpdateMesh();
	UFUNCTION(BlueprintCallable, Category = "Selection Area")
	void GenerateCuboidMesh(float MLength, float MBreath, float MHeight);


	UFUNCTION(BlueprintCallable, Category = "Selection Area")
	void GenerateSphere(float Radius, int32 Segments, int32 Rings);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	int32 MLength = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	int32 MBreath = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	int32 MHeight = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	int32 MRadius = 100;
};
