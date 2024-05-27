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
}

void AFenceMeshActor::BeginPlay()
{
    Super::BeginPlay();

    if (!Spline || !Mesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spline or PillarMesh is not set."));
        return;
    }

    ClearPreviousAttachedMesh();
}

void AFenceMeshActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (!Spline || !Mesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spline or PillarMesh is not set."));
        return;
    }

    ClearPreviousAttachedMesh();

    int NumberOfSplinePoints = Spline->GetNumberOfSplinePoints();

    for (int i = 1; i < NumberOfSplinePoints; i++)
    {
        FVector StartPos = Spline->GetLocationAtSplinePoint(i - 1, ESplineCoordinateSpace::Local);
        FVector EndPos = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);

        FVector Direction = (EndPos - StartPos).GetSafeNormal();
        float SegmentLength = FVector::Distance(StartPos, EndPos);
        int NumberOfPillars = FMath::FloorToInt(SegmentLength / FenceProperties.Spacing);

        // Create pillars
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





            //FVector PillarPos = StartPos + Direction * (j * FenceProperties.Spacing);

            //FTransform PillarTransform;
            //PillarTransform.SetLocation(PillarPos);
            //PillarTransform.SetRotation(FQuat::Identity);
            //PillarTransform.SetScale3D(FVector(0.15f)); // Adjust scale as needed

            //if (AVerticalRailActor* NewPillar = GetWorld()->SpawnActor<AVerticalRailActor>(PillarActorClass, PillarTransform))
            //{
            //    NewPillar->RegisterAllComponents();
            //    SpawnedPillars.Add(NewPillar);
            //}
        }

        // Create horizontal fences between pillars
        if (HorizontalFenceStaticMesh)
        {
            CreateHorizontalFence(StartPos, EndPos);
        }
    }
}

void AFenceMeshActor::ClearPreviousAttachedMesh()
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

void AFenceMeshActor::CreateHorizontalFence(const FVector& StartPos, const FVector& EndPos)
{
    FVector MidPoint = (StartPos + EndPos) / 2;
    FVector FenceDirection = (EndPos - StartPos).GetSafeNormal();
    float FenceLength = FVector::Distance(StartPos, EndPos) / 100.0f;

    float Width = FenceProperties.Width / 100.0f;
    float Height = FenceProperties.Height / 150.0f;

    FRotator FenceRotation = FenceDirection.Rotation();

    UStaticMeshComponent* HorizontalFence1 = NewObject<UStaticMeshComponent>(this);
    HorizontalFence1->RegisterComponent();
    HorizontalFence1->SetWorldScale3D(FVector(FenceLength, Width, Height));
    HorizontalFence1->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);
    HorizontalFence1->SetRelativeLocation(MidPoint + FVector(0, 0, Height * 100.0f));
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
    HorizontalFence2->SetRelativeLocation(MidPoint + FVector(0, 0, Height * 400.0f));
    HorizontalFence2->SetRelativeRotation(FenceRotation);
    HorizontalFence2->SetStaticMesh(HorizontalFenceStaticMesh);
    if (FenceMaterial)
    {
        HorizontalFence2->SetMaterial(0, FenceMaterial);
    }
    SplineMeshes.Add(HorizontalFence2);
}
