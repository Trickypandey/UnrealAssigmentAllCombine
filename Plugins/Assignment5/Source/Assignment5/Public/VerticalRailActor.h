// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent/Public/ProceduralMeshComponent.h"
#include "VerticalRailActor.generated.h"

UCLASS()
class ASSIGNMENT5_API AVerticalRailActor : public AActor
{
	GENERATED_BODY()
	
public:
	void InitialPillarGeneration();
	void RoundTurnedCapital();
	void WindsorTurnedCapital();
	void PyramidTop();
	void ACornCapital();
	void GothicStarCapital();
	void RoundedOverTopCapital();
	void GenerateSphere(float Radius, int32 Segments, int32 Rings);
	void GenerateCylinder(float Radius, float Height, int32 Segments);
	void GenerateCone(float Radius, float Height, int32 Segments);
	void GenerateBellShape(float BaseRadius, float Height, float RimRadius, float CurvatureFactor, int NumSlices,
	                       int NumStacks);
	void GenerateTorus(float InnerRadius, float OuterRadius, int32 RadialSegments, int32 TubularSegments);
	void GenerateSemiEggShape(int32 NumSegments, float RadiusX, float RadiusY, float Height, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals, TArray<FVector2D>& UVs, TArray<FProcMeshTangent>& Tangents, TArray<FLinearColor>& VertexColors);
	void GenerateInvertedSemiEggShape(int32 NumSegments, float RadiusX, float RadiusY, float Height, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals, TArray<FVector2D>& UVs, TArray<FProcMeshTangent>& Tangents, TArray<FLinearColor>& VertexColors);
	void GenerateCornShape(int32 NumSegments, float BaseRadiusX, float BaseRadiusY, float Height);
	void GeneratePyramid(float BaseLength, float Height);
	void GenerateFenceTop(float Radius, float Length, float Width);
	// Sets default values for this actor's properties
	AVerticalRailActor();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GenerateCylinderMesh(float Radius, float Height, int32 NumSegments);
	void GenerateCylinder(FVector Location, float Radius, float Height, int32 Segments);
	void GenerateCuboidMesh(float Width, float Depth, int32 Height);

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* ProceduralMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cylinder Properties")
	int32 MHeight = 180;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cylinder Properties")
	float MRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cylinder Properties")
	int32 MSides;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cuboid Properties")
	float MSide = 7.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rail Settings")
	float TopMeshLerpValue;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	TArray<FVector> MVertices;

	UPROPERTY(EditAnywhere)
	TArray<int32> MTriangles;

	UPROPERTY()
	FVector MLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BottomSide = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TopSide = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BottomHeight = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Scale = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rail Settings")
	int32 Index = 0.0f;

	
	int32 Segment = 0;

	UPROPERTY()
	UMaterialInstanceDynamic* FenceMaterial;

};
