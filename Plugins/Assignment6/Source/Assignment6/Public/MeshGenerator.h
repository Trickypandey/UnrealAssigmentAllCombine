#pragma once

#include "CoreMinimal.h"
#include "AsyncScatterTask.h"
#include "ScatterDataAsset.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MeshGenerator.generated.h"

UCLASS()
class ASSIGNMENT6_API AMeshGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMeshGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	UPROPERTY(EditAnywhere, Category = "Scatter")
	UScatterDataAsset* DataAsset;
	UPROPERTY(EditAnywhere, Category = "Scatter")
	FVector Location;
	UPROPERTY(EditAnywhere, Category = "Scatter")
	FString Type;
	UPROPERTY(EditAnywhere, Category = "Scatter")
	FVector Scale;


	UPROPERTY(EditAnywhere, Category = "Scatter")
	int32 NumberOfInstances = 100;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Defaults)
	UBoxComponent* BoundingVolume;

	UFUNCTION(BlueprintCallable)
	void ScatterObjects(int N, FVector Scale_, FVector Location_, FString Type_);

	void AddInstances(UStaticMesh* StaticMesh, const TArray<FTransform>& Transforms);
	void FinishScatter();
	FAsyncTask<AsyncScatterTask>* mAsyncScatterTask;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateProgressBar(float percent);
private:


	UPROPERTY()
	TMap<UStaticMesh*, UHierarchicalInstancedStaticMeshComponent*> HISMComponents;

	FScopedSlowTask* SlowTask;
};
