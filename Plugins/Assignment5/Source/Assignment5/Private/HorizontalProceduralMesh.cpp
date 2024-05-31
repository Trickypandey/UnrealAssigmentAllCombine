#include "HorizontalProceduralMesh.h"

#include "VerticalRailActor.h"

// Sets default values
AHorizontalProceduralMesh::AHorizontalProceduralMesh()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    ProcMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcMeshComponent"));
    RootComponent = ProcMeshComponent;

}

// Called when the game starts or when spawned
void AHorizontalProceduralMesh::BeginPlay()
{
	Super::BeginPlay();

}

void AHorizontalProceduralMesh::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

    //GenerateHorizontalCuboidMesh(20,100,20);
    GenerateCylinder(1.0f, 100, 20);
}

// Called every frame
void AHorizontalProceduralMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




void AHorizontalProceduralMesh::GenerateCylinder(float Radius, float Height, int32 Segments)
{
    // ProcMeshComponent->ClearAllMeshSections();

    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FProcMeshTangent> Tangents;
    TArray<FLinearColor> Colors;

    // Generate the vertices, normals, UVs, and tangents for the cylinder
    for (int32 s = 0; s <= Segments; s++)
    {
        float Angle = static_cast<float>(s) / Segments * 2.0f * PI;
        float Y = Radius * FMath::Cos(Angle); // Rotate along Y-axis for horizontal cylinder
        float Z = Radius * FMath::Sin(Angle);

        Vertices.Add(FVector(Height / 2.0f, Y, Z));  // Adjust the position along X-axis for horizontal cylinder
        Vertices.Add(FVector(-Height / 2.0f, Y, Z)); // Adjust the position along X-axis for horizontal cylinder

        Normals.Add(FVector(0.0f, FMath::Cos(Angle), FMath::Sin(Angle))); // Normals aligned with cylinder direction
        Normals.Add(FVector(0.0f, FMath::Cos(Angle), FMath::Sin(Angle)));

        UVs.Add(FVector2D(static_cast<float>(s) / Segments, 0.0f));
        UVs.Add(FVector2D(static_cast<float>(s) / Segments, 1.0f));

        FVector TangentX = FVector(0.0f, -FMath::Sin(Angle), FMath::Cos(Angle)); // Tangent aligned with cylinder direction
        FVector TangentY = FVector(1.0f, 0.0f, 0.0f); // Tangent along X-axis for horizontal cylinder
        FVector TangentZ = FVector(0.0f, 0.0f, 1.0f);

        Tangents.Add(FProcMeshTangent(TangentX, false));
        Tangents.Add(FProcMeshTangent(TangentY, false));
    }

    // Generate the triangle indices for the sides of the cylinder
    for (int32 s = 0; s < Segments; s++)
    {
        int32 i0 = s * 2;
        int32 i1 = i0 + 1;
        int32 i2 = (s + 1) * 2;
        int32 i3 = i2 + 1;

        // Outer side
        Triangles.Add(i0);
        Triangles.Add(i2);
        Triangles.Add(i1);

        Triangles.Add(i1);
        Triangles.Add(i2);
        Triangles.Add(i3);

        // Inner side (reverse winding)
        Triangles.Add(i0);
        Triangles.Add(i1);
        Triangles.Add(i2);

        Triangles.Add(i1);
        Triangles.Add(i3);
        Triangles.Add(i2);
    }

    // Add the cylinder caps
    AddCylinderCaps(Vertices, Triangles, Normals, UVs, Colors, Tangents, Radius, Height / 2.0f, Segments);
    AddCylinderCaps(Vertices, Triangles, Normals, UVs, Colors, Tangents, Radius, -Height / 2.0f, Segments);

    // Generate the vertex colors
    for (int32 i = 0; i < Vertices.Num(); i++)
    {
        Colors.Add(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
    }

    // Add the mesh to the procedural mesh component
    ProcMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
}



void AHorizontalProceduralMesh::AddCylinderCaps(
    TArray<FVector>& Vertices,
    TArray<int32>& Triangles,
    TArray<FVector>& Normals,
    TArray<FVector2D>& UVs,
    TArray<FLinearColor>& Colors,
    TArray<FProcMeshTangent>& Tangents,
    float Radius,
    float HalfHeight,
    int32 Segments)
{
    int32 CapCenterBottomIndex = Vertices.Num();
    Vertices.Add(FVector(-HalfHeight, 0.0f, 0.0f));
    Normals.Add(FVector(0.0f, -1.0f, 0.0f)); // Normal pointing downward
    UVs.Add(FVector2D(0.5f, 0.5f)); // Center UV
    Colors.Add(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
    Tangents.Add(FProcMeshTangent(FVector(1.0f, 0.0f, 0.0f), false));

    int32 CapCenterTopIndex = Vertices.Num();
    Vertices.Add(FVector(HalfHeight, 0.0f, 0.0f));
    Normals.Add(FVector(0.0f, 1.0f, 0.0f)); // Normal pointing upward
    UVs.Add(FVector2D(0.5f, 0.5f)); // Center UV
    Colors.Add(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
    Tangents.Add(FProcMeshTangent(FVector(1.0f, 0.0f, 0.0f), false));

    for (int32 s = 0; s <= Segments; s++)
    {

        float Angle = static_cast<float>(s) / Segments * 2.0f * PI;
        float X = Radius * FMath::Cos(Angle);
        float Y = Radius * FMath::Sin(Angle);

        FVector BottomVertex = FVector(-HalfHeight, X, Y);
        FVector TopVertex = FVector(HalfHeight, X, Y);

        Vertices.Add(BottomVertex);
        Vertices.Add(TopVertex);

        // Normals for the caps pointing outward
        FVector BottomNormal = FVector(0.0f, 0.0f, -1.0f); // Normal pointing downward
        FVector TopNormal = FVector(0.0f, 0.0f, 1.0f); // Normal pointing upward

        Normals.Add(BottomNormal);
        Normals.Add(TopNormal);

        // UVs mapping the vertices to a unit circle
        FVector2D BottomUV = FVector2D(0.5f + X / (2.0f * Radius), 0.5f + Y / (2.0f * Radius));
        FVector2D TopUV = FVector2D(0.5f + X / (2.0f * Radius), 0.5f + Y / (2.0f * Radius));

        UVs.Add(BottomUV);
        UVs.Add(TopUV);

        Colors.Add(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        Colors.Add(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

        Tangents.Add(FProcMeshTangent(FVector(1.0f, 0.0f, 0.0f), false));
        Tangents.Add(FProcMeshTangent(FVector(1.0f, 0.0f, 0.0f), false));

        if (s < Segments)
        {
            int32 BottomIndex0 = CapCenterBottomIndex + s * 2 + 2;
            int32 BottomIndex1 = BottomIndex0 + 2;

            int32 TopIndex0 = CapCenterTopIndex + s * 2 + 2;
            int32 TopIndex1 = TopIndex0 + 2;

            // Adding triangles for the caps
            Triangles.Add(CapCenterBottomIndex);
            Triangles.Add(BottomIndex0);
            Triangles.Add(BottomIndex1);

            Triangles.Add(CapCenterTopIndex);
            Triangles.Add(TopIndex1);
            Triangles.Add(TopIndex0);
        }
    }
}




void AHorizontalProceduralMesh::GenerateCuboidMesh(float Width, float Depth, int32 Height)
{
    TArray<FVector> Vertices;

    float L = Width;  // Half width
    float W = Depth;  // Half depth
    float H = Height;     // Full height

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

    ProcMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>(), TArray<FProcMeshTangent>(), true);
}