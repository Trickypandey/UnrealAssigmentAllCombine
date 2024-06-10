// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionArea.h"

// Sets default values
ASelectionArea::ASelectionArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
    SetRootComponent(ProceduralMesh);

	SelectionAreaType = ESelectionAreaType::Sphere;

}

void ASelectionArea::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	//UpdateMesh();
	if (SelectionAreaType == ESelectionAreaType::Box)
	{
		GenerateCuboidMesh(MLength, MBreath, MHeight);
		
	}
	else
	{
		
		GenerateSphere(MRadius, 20, 20);
	}
}

void ASelectionArea::ToggleShape()
{
    bIsSphere = !bIsSphere;
    if (bIsSphere)
    {
        GenerateSphere(100, 20, 20);
    }
    else
    {
	    GenerateCuboidMesh(MLength, MBreath, MHeight);
        
    }
}

// Called when the game starts or when spawned
void ASelectionArea::BeginPlay()
{
	Super::BeginPlay();
    bIsSphere = false;
    GenerateCuboidMesh(MLength, MBreath, MHeight);
    //GenerateSphere(MRadius, 20, 20);
	
}

// Called every frame
void ASelectionArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASelectionArea::UpdateMesh()
{
	/*if (SelectionAreaType == ESelectionAreaType::Sphere && SphereMesh)
	{
		MeshComponent->SetStaticMesh(SphereMesh);
	}
	else if (SelectionAreaType == ESelectionAreaType::Box && BoxMesh)
	{
		MeshComponent->SetStaticMesh(BoxMesh);
	}*/
}



void ASelectionArea::GenerateCuboidMesh(float Length, float Breath, float Height)
{
    ProceduralMesh->ClearAllMeshSections();
    TArray<FVector> Vertices;

    float L = Length;  // Half width
    float W = Breath;  // Half depth
    float H = Height*2;     // Full height

    // Front Face
    Vertices.Add(FVector(-L, -W, 0));  // 0
    Vertices.Add(FVector(-L, W, 0));   // 1
    Vertices.Add(FVector(-L, W, H));   // 2
    Vertices.Add(FVector(-L, -W, H));  // 3

    // Bottom Face
    Vertices.Add(FVector(-L, -W, 0));  // 4
    Vertices.Add(FVector(L, -W, 0));   // 5
    Vertices.Add(FVector(L, W, 0));    // 6
    Vertices.Add(FVector(-L, W, 0));   // 7

    // Back Face
    Vertices.Add(FVector(L, -W, 0));   // 8
    Vertices.Add(FVector(L, -W, H));   // 9
    Vertices.Add(FVector(L, W, H));    // 10
    Vertices.Add(FVector(L, W, 0));    // 11

    // Top Face
    Vertices.Add(FVector(L, -W, H));   // 12
    Vertices.Add(FVector(-L, -W, H));  // 13
    Vertices.Add(FVector(-L, W, H));   // 14
    Vertices.Add(FVector(L, W, H));    // 15

    // Left Face
    Vertices.Add(FVector(-L, -W, H));  // 16
    Vertices.Add(FVector(L, -W, H));   // 17
    Vertices.Add(FVector(L, -W, 0));   // 18
    Vertices.Add(FVector(-L, -W, 0));  // 19

    // Right Face
    Vertices.Add(FVector(-L, W, H));   // 20
    Vertices.Add(FVector(-L, W, 0));   // 21
    Vertices.Add(FVector(L, W, 0));    // 22
    Vertices.Add(FVector(L, W, H));    // 23

    // Triangles
    TArray<int32> Triangles = {
        0, 1, 3, 1, 2, 3,  // Front Face
        4, 5, 7, 5, 6, 7,  // Bottom Face
        8, 9, 11, 9, 10, 11,  // Back Face
        12, 13, 15, 13, 14, 15,  // Top Face
        16, 17, 19, 17, 18, 19,  // Left Face
        20, 21, 23, 21, 22, 23   // Right Face
    };

    TArray<FVector2D> UVs = {
        FVector2D(0, 1), FVector2D(1, 1), FVector2D(1, 0), FVector2D(0, 0), // Front Face
        FVector2D(0, 0), FVector2D(0, 1), FVector2D(1, 1), FVector2D(1, 0), // Bottom Face
        FVector2D(1, 1), FVector2D(1, 0), FVector2D(0, 0), FVector2D(0, 1), // Back Face
        FVector2D(0, 0), FVector2D(0, 1), FVector2D(1, 1), FVector2D(1, 0), // Top Face
        FVector2D(1, 0), FVector2D(0, 0), FVector2D(0, 1), FVector2D(1, 1), // Left Face
        FVector2D(0, 0), FVector2D(0, 1), FVector2D(1, 1), FVector2D(1, 0)  // Right Face
    };

    TArray<FVector> Normals = {
        FVector(-1, 0, 0), FVector(-1, 0, 0), FVector(-1, 0, 0), FVector(-1, 0, 0), // Front Face
        FVector(0, 0, -1), FVector(0, 0, -1), FVector(0, 0, -1), FVector(0, 0, -1), // Bottom Face
        FVector(1, 0, 0), FVector(1, 0, 0), FVector(1, 0, 0), FVector(1, 0, 0), // Back Face
        FVector(0, 0, 1), FVector(0, 0, 1), FVector(0, 0, 1), FVector(0, 0, 1), // Top Face
        FVector(0, -1, 0), FVector(0, -1, 0), FVector(0, -1, 0), FVector(0, -1, 0), // Left Face
        FVector(0, 1, 0), FVector(0, 1, 0), FVector(0, 1, 0), FVector(0, 1, 0)  // Right Face
    };

    ProceduralMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>(), TArray<FProcMeshTangent>(), true);
    if (Material)
    {
        ProceduralMesh->SetMaterial(0,Material);
    }

    ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    ProceduralMesh->SetCollisionObjectType(ECC_WorldDynamic);
    ProceduralMesh->SetCollisionResponseToAllChannels(ECR_Block);
}

void ASelectionArea::GenerateSphere(float Radius, int32 Segments, int32 Rings)
{
    // Clear previous mesh data
    ProceduralMesh->ClearAllMeshSections();

    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FProcMeshTangent> Tangents;
    TArray<FLinearColor> Colors;

    // Generate vertices, normals, UVs, and tangents
    for (int r = 0; r <= Rings; ++r)
    {
        float Phi = PI * r / Rings;
        for (int s = 0; s <= Segments; ++s)
        {
            float Theta = 2 * PI * s / Segments;
            FVector Pos = FVector(Radius * FMath::Sin(Phi) * FMath::Cos(Theta), Radius * FMath::Sin(Phi) * FMath::Sin(Theta), Radius * FMath::Cos(Phi));
            Vertices.Add(Pos);
            Normals.Add(Pos.GetSafeNormal());
            UVs.Add(FVector2D(static_cast<float>(s) / Segments, static_cast<float>(r) / Rings));
            FVector Tangent = FVector(-FMath::Sin(Theta), FMath::Cos(Theta), 0).GetSafeNormal();
            Tangents.Add(FProcMeshTangent(Tangent, false));
            Colors.Add(FLinearColor(1, 1, 1, 1));
        }
    }

    // Generate triangles for top cap
    for (int s = 0; s < Segments; ++s)
    {
        Triangles.Add(0);
        Triangles.Add(1 + s);
        Triangles.Add(1 + (s + 1) % Segments);
    }

    // Generate triangles for body
    for (int r = 0; r < Rings; ++r)
    {
        for (int s = 0; s < Segments; ++s)
        {
            int Current = r * (Segments + 1) + s;
            int Next = Current + 1;
            int Below = Current + (Segments + 1);
            int BelowNext = Below + 1;

            // First triangle
            Triangles.Add(Current);
            Triangles.Add(BelowNext);
            Triangles.Add(Next);

            // Second triangle
            Triangles.Add(Current);
            Triangles.Add(Below);
            Triangles.Add(BelowNext);
        }
    }

    // Generate triangles for bottom cap
    int BottomVertexIndex = Vertices.Num() - 1;
    for (int s = 0; s < Segments; ++s)
    {
        Triangles.Add(BottomVertexIndex);
        Triangles.Add(BottomVertexIndex - (Segments + 1) + s);
        Triangles.Add(BottomVertexIndex - (Segments + 1) + (s + 1) % Segments);
    }

    // Create the mesh section
    ProceduralMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
}