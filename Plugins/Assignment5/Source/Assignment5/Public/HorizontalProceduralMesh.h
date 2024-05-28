#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent/Public/ProceduralMeshComponent.h"
#include "HorizontalProceduralMesh.generated.h"

UCLASS()
class ASSIGNMENT5_API AHorizontalProceduralMesh : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHorizontalProceduralMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GenerateHorizontalCuboidMesh(float Width, float Depth, float Height);

	UFUNCTION(BlueprintCallable, Category = Defauls)
	void GenerateCylinder(float Radius, float Height, int32 Segments);

	UFUNCTION()
	void AddCylinderCaps(TArray<FVector>& Vertices,
		TArray<int32>& Triangles,
		TArray<FVector>& Normals,
		TArray<FVector2D>& UVs,
		TArray<FLinearColor>& Colors,
		TArray<FProcMeshTangent>& Tangents,
		float Radius,
		float HalfHeight,
		int32 Segments);

	UProceduralMeshComponent* ProcMeshComponent;
};
