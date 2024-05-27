// Fill out your copyright notice in the Description page of Project Settings.


#include "FenceMeshActor.h"

// Sets default values
AFenceMeshActor::AFenceMeshActor()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    RootComponent = SceneComponent;

    Spline = CreateDefaultSubobject<USplineComponent>("Spline");
    Spline->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AFenceMeshActor::BeginPlay()
{
    Super::BeginPlay();
}

void AFenceMeshActor::AttachMesh(const FVector& Location, const FRotator& Rotation)
{
    

    /*USplineMeshComponent* MeshComponent = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());

   
	MeshComponent->SetStaticMesh(Mesh);
    
    MeshComponent->SetMobility(EComponentMobility::Movable);
    MeshComponent->SetRelativeLocation(Location);
    MeshComponent->SetRelativeRotation(Rotation);
    MeshComponent->SetWorldScale3D(FVector(FenceProperties.Width, FenceProperties.Width, FenceProperties.Height));
    MeshComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
    MeshComponent->RegisterComponent();
    MeshComponents.Add(MeshComponent);*/

    if(VerticalRailActorClass)
    {
        FTransform Transform(Rotation, Location);
        AVerticalRailActor* NewMesh = GetWorld()->SpawnActor<AVerticalRailActor>(VerticalRailActorClass, Transform);

        if (NewMesh)
        {
            NewMesh->GenerateCuboidMesh(CuboidDimensions.X, CuboidDimensions.Y, CuboidDimensions.Z);
            AttachedMeshes.Add(NewMesh);
        }
    }
}

void AFenceMeshActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    ClearPreviousAttachedMesh();

    /*if (!Spline || !Mesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spline or Mesh is not set."));
        return;
    }

    float Distance = 0.0f;
    const float SplineLength = Spline->GetSplineLength();
    const int32 NumMeshes = FMath::FloorToInt(SplineLength / FenceProperties.Spacing);

    for (int32 i = 0; i < NumMeshes; ++i)
    {
        FVector Location = Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
        FRotator Rotation = Spline->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
        AttachMesh(Location, Rotation);

        Distance += FenceProperties.Spacing;
    }

    UE_LOG(LogTemp, Log, TEXT("Constructed fence with %d mesh components"), MeshComponents.Num());*/
}


void AFenceMeshActor::AttachCuboidMeshes()
{
    if (!VerticalRailActorClass || !Spline)
    {
        UE_LOG(LogTemp, Warning, TEXT("VerticalRailActorClass or SplineComponent is not set."));
        return;
    }

    const float SplineLength = Spline->GetSplineLength();
    const int32 NumMeshes = FMath::FloorToInt(SplineLength / FenceProperties.Spacing);

    for (int32 i = 0; i <= NumMeshes; ++i)
    {
        float Distance = i * FenceProperties.Spacing;
        FVector Location = Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
        FRotator Rotation = Spline->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
        AttachMesh(Location, Rotation);
    }
}

void AFenceMeshActor::ClearPreviousAttachedMesh()
{
    for (UStaticMeshComponent* MeshComponent : MeshComponents)
    {
        if (MeshComponent)
        {
            MeshComponent->DestroyComponent();
        }
    }
    MeshComponents.Empty();
}

// Called every frame
void AFenceMeshActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}