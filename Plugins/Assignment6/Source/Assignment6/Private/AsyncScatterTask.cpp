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

					/*FVector BoundingExtent = MeshGenerator->BoundingVolume->GetScaledBoxExtent();
					FVector Origin = MeshGenerator->BoundingVolume->GetComponentLocation();
					FBox BoundingBox(Origin - BoundingExtent, Origin + BoundingExtent);*/
					FVector Position;
					if (MeshGenerator->Type == "Box") {
						FVector BoundingExtent = MeshGenerator->Scale * 100;
						FVector Origin = MeshGenerator->Location;
						FBox BoundingBox(Origin - BoundingExtent, Origin + BoundingExtent);

						Position = FMath::RandPointInBox(BoundingBox);
					}
					else {
						//Sphere
						float Radius = MeshGenerator->Scale.Z * 100;
						FVector Origin = MeshGenerator->Location;
						Position = FMath::VRand() * FMath::FRandRange(0.0f, Radius) + Origin;
					}
					//InstanceTransforms.Add(FTransform(Position));
					GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "ahfdklagsdf");
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