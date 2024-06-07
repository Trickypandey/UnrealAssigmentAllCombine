#include "AsyncScatterTask.h"

#include "MeshGenerator.h"
#include "ScatterDataAsset.h"
#include "Async/ParallelFor.h"

AsyncScatterTask::AsyncScatterTask(AMeshGenerator* MeshGenerator)
{
	this->MeshGenerator = MeshGenerator;
}

void AsyncScatterTask::DoWork()
{
	if (MeshGenerator)
	{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("do work")));
		if (UScatterDataAsset* DataAsset = MeshGenerator->DataAsset.Get())
		{
			TArray<UStaticMesh*> StaticMeshes = DataAsset->StaticMeshes;

			// ParallelFor(100, [](int32 ThreadIndex)
			// {
			// 	
			// });
			//



			for (int jIndex = 0; jIndex < StaticMeshes.Num(); jIndex++)
			{
				//int32 RandomMeshIndex = FMath::RandRange(0, StaticMeshes.Num() - 1);
				UStaticMesh* CurrentMesh = StaticMeshes[jIndex];



				for (int iIndex = 0; iIndex < MeshGenerator->NumberOfInstances; iIndex++)
				{

					FVector BoundingExtent = MeshGenerator->BoundingVolume->GetScaledBoxExtent();
					FVector Origin = MeshGenerator->BoundingVolume->GetComponentLocation();
					FBox BoundingBox(Origin - BoundingExtent, Origin + BoundingExtent);

					FVector Position = FMath::RandPointInBox(BoundingBox);
					//InstanceTransforms.Add(FTransform(Position));

					TArray<FTransform> InstanceTransforms;
					InstanceTransforms.Add(FTransform(Position));
					MeshGenerator->AddInstances(CurrentMesh, InstanceTransforms);
				}


			}

		}

		AsyncTask(ENamedThreads::GameThread, [this]()
			{
				MeshGenerator->FinishScatter();
			});
	}
}