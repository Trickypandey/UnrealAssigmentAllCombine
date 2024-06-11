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
	if (IsValid(MeshGenerator) && MeshGenerator)
	{
		if (UScatterDataAsset* DataAsset = MeshGenerator->DataAsset)
		{
			TArray<UStaticMesh*> StaticMeshes = DataAsset->StaticMeshes;


			for (int jIndex = 0; jIndex < StaticMeshes.Num(); jIndex++)
			{
				UStaticMesh* CurrentMesh = StaticMeshes[jIndex];



				for (int iIndex = 0;  IsValid(MeshGenerator) && iIndex < MeshGenerator->NumberOfInstances; iIndex++)
				{

					FVector Position;
					if (MeshGenerator->Type == "Cube") {
						// BOX
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
					float Progress = (float)(((jIndex)*MeshGenerator->NumberOfInstances) + (iIndex + 1)) / static_cast<float>(MeshGenerator->NumberOfInstances * DataAsset->StaticMeshes.Num());

					TArray<FTransform> InstanceTransforms;
					InstanceTransforms.Add(FTransform(Position));
					MeshGenerator->AddInstances(CurrentMesh, InstanceTransforms);
					FPlatformProcess::Sleep(0.01f);
					AsyncTask(ENamedThreads::GameThread, [this,Progress]()
						{
							MeshGenerator->UpdateProgressBar(Progress);
							//MeshGenerator->FinishScatter();
							
						});
				}


			}

		}

	}
}