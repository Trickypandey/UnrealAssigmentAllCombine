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
    static ConstructorHelpers::FObjectFinder<UDataTable> Fence_DT(TEXT("/Script/Engine.DataTable'/Assignment5/DataTable/DT_FenceType.DT_FenceType'"));
    if (Fence_DT.Succeeded())
    {
        DataTable_Fence = Fence_DT.Object;
    }

    
}

void AFenceMeshActor::LoadFenceData()
{
    if (DataTable_Fence)
    {
        DataTable_Fence->GetAllRows<FFenceTypes>(TEXT("FenceDataTable"), FenceRows);

        for (auto i  : FenceRows)
        {
	        if(i->Name ==  CurrentFenceType)
	        {
                CurrentFFenceTypes.FenceMesh = i->FenceMesh;
                CurrentFFenceTypes.Fence = i->Fence;
                CurrentFFenceTypes.Name = i->Name;
                break;
	        }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("DataTable_Fence is not set"));
    }
}


void AFenceMeshActor::BeginPlay()
{
    Super::BeginPlay();

    if (!Spline || !CurrentFFenceTypes.FenceMesh)
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

    LoadFenceData();

    if (!Spline && !CurrentFFenceTypes.FenceMesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spline or PillarMesh is not set."));
        return;
    }

    ClearPreviousAttachedMesh(true);
    CreateStaticMeshes();

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
        int NumberOfPillars = FMath::CeilToInt(SegmentLength / FenceProperties.Spacing);

        float InternalSpacing = SegmentLength / (NumberOfPillars - 1);

        for (int j = 0; j < NumberOfPillars; ++j)
        {
            FVector PillarPos = StartPos + Direction * (j * InternalSpacing);

            FString PillarName = FString::Printf(TEXT("Pillar_%d_%d"), i, j);
            UStaticMeshComponent* NewPillar = NewObject<UStaticMeshComponent>(this, FName(*PillarName));
            NewPillar->SetStaticMesh(CurrentFFenceTypes.FenceMesh);
            NewPillar->SetRelativeLocation(PillarPos);
            NewPillar->SetupAttachment(Spline);
            NewPillar->SetRelativeScale3D(FVector(1.f,1.f,FenceProperties.Length/100)); // Adjust scale as needed
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


void AFenceMeshActor::CreateHorizontalFence(const FVector& StartPos, const FVector& EndPos)
{
    FVector MidPoint = (StartPos + EndPos) / 2;
    FVector FenceDirection = (EndPos - StartPos).GetSafeNormal();
    float FenceLength = FVector::Distance(StartPos, EndPos) / 100.0f;

    float Width = FenceProperties.Width / 100.0f;
    float Height = FenceProperties.Width / 100.0f;

    FRotator FenceRotation = FenceDirection.Rotation();
   
    UStaticMeshComponent* HorizontalFence1 = NewObject<UStaticMeshComponent>(this );
    HorizontalFence1->RegisterComponent();
    HorizontalFence1->SetWorldScale3D(FVector(FenceLength, Width, Height));
    HorizontalFence1->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);
    HorizontalFence1->SetRelativeLocation(MidPoint + FVector(0, 0, (FenceProperties.Length*2)/5));
    HorizontalFence1->SetRelativeRotation(FenceRotation);
    HorizontalFence1->SetStaticMesh(HorizontalFenceStaticMesh);
    if (FenceMaterial)
    {
        HorizontalFence1->SetMaterial(0, FenceMaterial);
    }
    HorizontalSplineMeshes.Add(HorizontalFence1);

   
    UStaticMeshComponent* HorizontalFence2 = NewObject<UStaticMeshComponent>(this);
    HorizontalFence2->RegisterComponent();
    HorizontalFence2->SetWorldScale3D(FVector(FenceLength, Width, Height));
    HorizontalFence2->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);
    HorizontalFence2->SetRelativeLocation(MidPoint + FVector(0, 0, (FenceProperties.Length * 3) / 5));
    HorizontalFence2->SetRelativeRotation(FenceRotation);
    HorizontalFence2->SetStaticMesh(HorizontalFenceStaticMesh);
    if (FenceMaterial)
    {
        HorizontalFence2->SetMaterial(0, FenceMaterial);
    }
    int NumberOfSplinePoints = Spline->GetNumberOfSplinePoints();
  /*  for (int32 i{}; i < NumberOfSplinePoints; ++i)
    {
        Spline->SetSplinePointType(i, ESplinePointType::Linear);
    }*/
    HorizontalSplineMeshes.Add(HorizontalFence2);
}

void AFenceMeshActor::ClearPreviousAttachedMesh(bool Flag)
{

	    
	    for (UStaticMeshComponent* MeshComponent : SplineMeshes)
	    {
	        if (MeshComponent)
	        {
	            MeshComponent->DestroyComponent();
	        }
	    }
	    SplineMeshes.Empty();

       for ( auto* MeshComponent : HorizontalSplineMeshes)
       {
	       if (MeshComponent)
	       {
		       
			MeshComponent->DestroyComponent();
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
        float InternalSpacing = SegmentLength / NumberOfPillars;
        if (i != NumberOfSplinePoints - 1) NumberOfPillars--;

        // Spawn pillar actors
        for (int j = 0; j <= NumberOfPillars; ++j)
        {
            FVector PillarPos = StartPos + Direction * (j * InternalSpacing);

            FTransform PillarTransform;

            if (AVerticalRailActor* NewPillar = GetWorld()->SpawnActor<AVerticalRailActor>(CurrentFFenceTypes.Fence, PillarTransform))
            {
                NewPillar->RegisterAllComponents();
                NewPillar->AttachToComponent(Spline, FAttachmentTransformRules::KeepWorldTransform); // Attach to spline component
                NewPillar->SetActorRelativeLocation(PillarPos); // Set the relative location
                //NewPillar->GenerateCuboidMesh(3,3,FenceProperties.Height);

                NewPillar->BottomHeight = FenceProperties.Length;
                NewPillar->BottomSide = FenceProperties.Width;
                NewPillar->InitialPillarGeneration();
                
                if (FenceMaterial)
                {
	                if (UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(FenceMaterial, this))
                    {
                        for (int Sections = 0; Sections < NewPillar->ProceduralMesh->GetNumSections(); Sections++)
                        {
                            NewPillar->ProceduralMesh->SetMaterial(Sections, DynamicMaterial);
                        }

                    }
                }


                SpawnedPillars.Add(NewPillar);
                
            }
        }
    }
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
            AHorizontalProceduralMesh* HorizontalActor = GetWorld()->SpawnActor<AHorizontalProceduralMesh>(Location, Rotation);
            if (HorizontalActor)
            {
                // Optionally, set scale or other properties
                HorizontalActor->GenerateCylinder(FenceProperties.Width/2, Length, 20);
                //HorizontalActor->GenerateCuboidMesh(Length/100, FenceProperties.Width, FenceProperties.Length / 2500.0f);
                //CylinderActor->SetActorScale3D(Scale);
                
                if (FenceMaterial)
                {
                    UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(FenceMaterial, this);
                    if (DynamicMaterial)
                    {
                        DynamicMaterial->SetScalarParameterValue(FName("TileX"), Length / 100.0f); // Example scaling
                        //DynamicMaterial->SetScalarParameterValue(FName("TileY"), TileY);

                        for (int i = 0; i < HorizontalActor->ProcMeshComponent->GetNumSections(); i++)
                        {
                            HorizontalActor->ProcMeshComponent->SetMaterial(i, DynamicMaterial);
                        }

                    }
                }
            }

        }
    }


}