#include "FenceMeshActor.h"

AFenceMeshActor::AFenceMeshActor()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    RootComponent = SceneComponent;

    Spline = CreateDefaultSubobject<USplineComponent>("Spline");
    Spline->SetupAttachment(SceneComponent);

    // Default properties
    FenceProperties.Length = 100.0f;
    FenceProperties.Width = 5.0f;
    FenceProperties.Height = 18.0f;
    FenceProperties.Spacing = 20.0f;
    if (!DataTable_Fence)
    {
        static ConstructorHelpers::FObjectFinder<UDataTable> Fence_DT(TEXT("/Script/Engine.DataTable'/Assignment5/DataTable/BP_FenceType.BP_FenceType'"));
        DataTable_Fence = Fence_DT.Object;
    }
}

void AFenceMeshActor::BeginPlay()
{
    Super::BeginPlay();

    if (!Spline || !Mesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spline or PillarMesh is not set."));
        return;
    }

    SpawnPillarActors();
    ReplaceHorizontalMeshWithProceduralMesh();
    ClearPreviousAttachedMesh(true);
}

void AFenceMeshActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (!Spline || !Mesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spline or PillarMesh is not set."));
        return;
    }

    ClearPreviousAttachedMesh(true);
    CreateStaticMeshes();

    //int NumberOfSplinePoints = Spline->GetNumberOfSplinePoints();

    //for (int i = 1; i < NumberOfSplinePoints; i++)
    //{
    //    FVector StartPos = Spline->GetLocationAtSplinePoint(i - 1, ESplineCoordinateSpace::Local);
    //    FVector EndPos = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);

    //    FVector Direction = (EndPos - StartPos).GetSafeNormal();
    //    float SegmentLength = FVector::Distance(StartPos, EndPos);
    //    int NumberOfPillars = FMath::FloorToInt(SegmentLength / FenceProperties.Spacing);

    //    // Create pillars
    //    for (int j = 0; j <= NumberOfPillars; ++j)
    //    {
    //        FVector PillarPos = StartPos + Direction * (j * FenceProperties.Spacing);

    //        //FString PillarName = FString::Printf(TEXT("Pillar_%d_%d"), i, j);
    //        //UStaticMeshComponent* NewPillar = NewObject<UStaticMeshComponent>(this, FName(*PillarName));
    //        //NewPillar->SetStaticMesh(Mesh);
    //        //NewPillar->SetRelativeLocation(PillarPos);
    //        //NewPillar->SetupAttachment(Spline);
    //        //NewPillar->SetRelativeScale3D(FVector(0.15f)); // Adjust scale as needed
    //        //NewPillar->SetMobility(EComponentMobility::Movable);
    //        //if (FenceMaterial)
    //        //{
    //        //    NewPillar->SetMaterial(0, FenceMaterial);
    //        //}
    //        //NewPillar->RegisterComponent();
    //        //SplineMeshes.Add(NewPillar);





    //        FTransform PillarTransform;
    //        PillarTransform.SetRotation(FQuat::Identity);
    //        PillarTransform.SetScale3D(FVector(1)); // Adjust scale as needed

    //        if (AVerticalRailActor* NewPillar = GetWorld()->SpawnActor<AVerticalRailActor>(PillarActorClass, PillarTransform))
    //        {
    //            NewPillar->RegisterAllComponents();
    //            NewPillar->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform); // Attach to spline component
    //            NewPillar->SetActorRelativeLocation(PillarPos); // Set the relative location
    //            SpawnedPillars.Add(NewPillar);
    //        }

    //    }

    //    // Create horizontal fences between pillars
    //    if (HorizontalFenceStaticMesh)
    //    {
    //        CreateHorizontalFence(StartPos, EndPos);
    //    }
    //}
}

void AFenceMeshActor::CreateStaticMeshes()
{
    int NumberOfSplinePoints = Spline->GetNumberOfSplinePoints();

    for (int i = 1; i < NumberOfSplinePoints; i++)
    {
        FVector StartPos = Spline->GetLocationAtSplinePoint(i - 1, ESplineCoordinateSpace::Local);
        FVector EndPos = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);

        FVector Direction = (EndPos - StartPos).GetSafeNormal();
        float SegmentLength = FVector::Distance(StartPos, EndPos);
        int NumberOfPillars = FMath::FloorToInt(SegmentLength / FenceProperties.Spacing);

        // Create static mesh pillars
        for (int j = 0; j <= NumberOfPillars; ++j)
        {
            FVector PillarPos = StartPos + Direction * (j * FenceProperties.Spacing);

            FString PillarName = FString::Printf(TEXT("Pillar_%d_%d"), i, j);
            UStaticMeshComponent* NewPillar = NewObject<UStaticMeshComponent>(this, FName(*PillarName));
            NewPillar->SetStaticMesh(Mesh);
            NewPillar->SetRelativeLocation(PillarPos);
            NewPillar->SetupAttachment(Spline);
            NewPillar->SetRelativeScale3D(FVector(0.15f)); // Adjust scale as needed
            NewPillar->SetMobility(EComponentMobility::Movable);
            if (FenceMaterial)
            {
                NewPillar->SetMaterial(0, FenceMaterial);
            }
            NewPillar->RegisterComponent();
            SplineMeshes.Add(NewPillar);
        }

        // Create horizontal fences between pillars
        if (HorizontalFenceStaticMesh)
        {
            CreateHorizontalFence(StartPos, EndPos);
        }
    }
}

void AFenceMeshActor::SpawnPillarActors()
{
    int NumberOfSplinePoints = Spline->GetNumberOfSplinePoints();

    for (int i = 1; i < NumberOfSplinePoints; i++)
    {
        FVector StartPos = Spline->GetLocationAtSplinePoint(i - 1, ESplineCoordinateSpace::Local);
        FVector EndPos = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);

        FRotator Rt = Spline->GetRotationAtSplinePoint(i - 1, ESplineCoordinateSpace::Local);

        FVector Direction = (EndPos - StartPos).GetSafeNormal();
        float SegmentLength = FVector::Distance(StartPos, EndPos);
        int NumberOfPillars = FMath::FloorToInt(SegmentLength / FenceProperties.Spacing);

        // Spawn pillar actors
        for (int j = 0; j <= NumberOfPillars; ++j)
        {
            FVector PillarPos = StartPos + Direction * (j * FenceProperties.Spacing);

            FTransform PillarTransform;
            //PillarTransform.SetRotation(FQuat::Identity);
            PillarTransform.SetScale3D(FVector(1)); // Adjust scale as needed

            if (AVerticalRailActor* NewPillar = GetWorld()->SpawnActor<AVerticalRailActor>(PillarActorClass, PillarTransform))
            {
                NewPillar->RegisterAllComponents();
                NewPillar->AttachToComponent(Spline, FAttachmentTransformRules::KeepWorldTransform); // Attach to spline component
                NewPillar->SetActorRelativeLocation(PillarPos); // Set the relative location
                NewPillar->GenerateCuboidMesh(3,3,FenceProperties.Height);
                SpawnedPillars.Add(NewPillar);
                
            }
        }
    }
}

void AFenceMeshActor::ClearPreviousAttachedMesh(bool Flag)
{
    if(Flag)
    {
	    
	    for (UStaticMeshComponent* MeshComponent : SplineMeshes)
	    {
	        if (MeshComponent)
	        {
	            MeshComponent->DestroyComponent();
	        }
	    }
	    SplineMeshes.Empty();
    }
    else
    {
	    
	    for (auto* Pillar : SpawnedPillars)
	    {
			if(Pillar)
			{
	            Pillar->Destroy();
			}
	    }
	    SpawnedPillars.Empty();
    }

}

void AFenceMeshActor::CreateHorizontalFence(const FVector& StartPos, const FVector& EndPos)
{
    FVector MidPoint = (StartPos + EndPos) / 2;
    FVector FenceDirection = (EndPos - StartPos).GetSafeNormal();
    float FenceLength = FVector::Distance(StartPos, EndPos) / 100.0f;

    float Width = FenceProperties.Width / 100.0f;
    float Height = FenceProperties.Height / 150.0f;

    FRotator FenceRotation = FenceDirection.Rotation();
   
    UStaticMeshComponent* HorizontalFence1 = NewObject<UStaticMeshComponent>(this );
    HorizontalFence1->RegisterComponent();
    HorizontalFence1->SetWorldScale3D(FVector(FenceLength, Width, Height));
    HorizontalFence1->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);
    HorizontalFence1->SetRelativeLocation(MidPoint + FVector(0, 0, Height * 200.0f));
    HorizontalFence1->SetRelativeRotation(FenceRotation);
    HorizontalFence1->SetStaticMesh(HorizontalFenceStaticMesh);
    if (FenceMaterial)
    {
        HorizontalFence1->SetMaterial(0, FenceMaterial);
    }
    SplineMeshes.Add(HorizontalFence1);

   
    UStaticMeshComponent* HorizontalFence2 = NewObject<UStaticMeshComponent>(this);
    HorizontalFence2->RegisterComponent();
    HorizontalFence2->SetWorldScale3D(FVector(FenceLength, Width, Height));
    HorizontalFence2->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);
    HorizontalFence2->SetRelativeLocation(MidPoint + FVector(0, 0, Height * 500.0f));
    HorizontalFence2->SetRelativeRotation(FenceRotation);
    HorizontalFence2->SetStaticMesh(HorizontalFenceStaticMesh);
    if (FenceMaterial)
    {
        HorizontalFence2->SetMaterial(0, FenceMaterial);
    }
    SplineMeshes.Add(HorizontalFence2);
}


void AFenceMeshActor::ReplaceHorizontalMeshWithProceduralMesh()
{
    TArray<UStaticMeshComponent*> Components;
    GetComponents<UStaticMeshComponent>(Components);

    for (UStaticMeshComponent* Component : Components)
    {
        if (Component && !Component->GetName().StartsWith("Pillar"))
        {
            FVector Location = Component->GetComponentLocation();
            FRotator Rotation = Component->GetComponentRotation();
            FVector Scale = Component->GetComponentScale();

            // Calculate the length of the bamboo stick
            float Length = Scale.X * Component->GetStaticMesh()->GetBoundingBox().GetSize().X;
            float Radius = 5.0f; // Adjust the radius as necessary

            // Spawn procedural mesh actor at the location of the bamboo stick
            AHorizontalProceduralMesh* CylinderActor = GetWorld()->SpawnActor<AHorizontalProceduralMesh>(Location, Rotation);
            if (CylinderActor)
            {
                // Optionally, set scale or other properties
                CylinderActor->GenerateCylinder(8.0f, Length, 20);
                //CylinderActor->SetActorScale3D(Scale);

                if (FenceMaterial)
                {
                    //UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(FenceMaterial, this);
                    //if (DynamicMaterial)
                    //{
                    //    DynamicMaterial->SetScalarParameterValue(FName("TileX"), Length / 100.0f); // Example scaling
                    //    DynamicMaterial->SetScalarParameterValue(FName("TileY"), TileY);

                    //    for (int i = 0; i < CylinderActor->ProcMeshComponent->GetNumSections(); i++)
                    //    {
                    //        CylinderActor->ProcMeshComponent->SetMaterial(i, DynamicMaterial);
                    //    }

                    //}
                }
            }


            // Destroy the bamboo stick
            //Component->DestroyComponent();
        }
    }


}