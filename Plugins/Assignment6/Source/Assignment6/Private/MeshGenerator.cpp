#include "MeshGenerator.h"
#include "Misc/ScopedSlowTask.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

// Sets default values
AMeshGenerator::AMeshGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoundingVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundingVolume"));
	BoundingVolume->SetBoxExtent(FVector(1000));
	RootComponent = BoundingVolume;
}

// Called when the game starts or when spawned
void AMeshGenerator::BeginPlay()
{
	Super::BeginPlay();
	if (DataAsset)
	{
		UDataAsset* dAsset = DataAsset;

	}

}

// Called every frame
void AMeshGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMeshGenerator::ScatterObjects(int N, FVector Scale_, FVector Location_, FString Type_)
{
	NumberOfInstances = N;
	Location = Location_;
	Scale = Scale_;
	Type = Type_;
	if (Type == "Cube") {

		Location.Z += Scale.Z * 100;
	}

	for (auto& Pair : HISMComponents)
	{
		if (UHierarchicalInstancedStaticMeshComponent* HISM = Pair.Value)
		{
			HISM->ClearInstances();
		}
	}

	if (DataAsset)
	{
		SlowTask = new FScopedSlowTask(NumberOfInstances * DataAsset->StaticMeshes.Num(), FText::FromString("Scattering Objects..."));
		SlowTask->MakeDialog(true);
	}

	if (mAsyncScatterTask && !mAsyncScatterTask->IsDone())
	{
		mAsyncScatterTask->EnsureCompletion();
		delete mAsyncScatterTask;
		mAsyncScatterTask = nullptr;
	}

	mAsyncScatterTask = new FAsyncTask<AsyncScatterTask>(this);
	mAsyncScatterTask->StartBackgroundTask();
}
void AMeshGenerator::AddInstances(UStaticMesh* StaticMesh, const TArray<FTransform>& Transforms)
{
		AsyncTask(ENamedThreads::GameThread, [this, StaticMesh, Transforms]()
			{
			UHierarchicalInstancedStaticMeshComponent** HISMCPtr = HISMComponents.Find(StaticMesh);
				if (HISMCPtr && *HISMCPtr && (*HISMCPtr)->IsValidLowLevel())
				{
							(*HISMCPtr)->AddInstances(Transforms, false);
							if (SlowTask)
							{
								SlowTask->EnterProgressFrame(Transforms.Num(), FText::FromString("Scattering Mesh : " + StaticMesh->GetName()));
							}

				}
				else
				{


						UHierarchicalInstancedStaticMeshComponent* NewHISMC = NewObject<UHierarchicalInstancedStaticMeshComponent>(this);
						NewHISMC->SetStaticMesh(StaticMesh);

						HISMComponents.Add(StaticMesh, NewHISMC);
							NewHISMC->RegisterComponentWithWorld(GetWorld());
							NewHISMC->AddInstances(Transforms, false);
							if (SlowTask)
							{
								SlowTask->EnterProgressFrame(Transforms.Num(), FText::FromString("Scattering Mesh : " + StaticMesh->GetName()));
							}



				}
			});
}
void AMeshGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

UFUNCTION(BlueprintImplementableEvent)
	void UpdateProgressBar(float percent);

void AMeshGenerator::FinishScatter()
{
	if (SlowTask)
	{
		SlowTask->Destroy();
	}
}
