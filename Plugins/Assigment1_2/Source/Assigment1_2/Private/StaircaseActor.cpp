// Fill out your copyright notice in the Description page of Project Settings.


#include "StaircaseActor.h"

// Sets default values
AStaircaseActor::AStaircaseActor()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	StepSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = StepSceneComponent;

	
}

// Called when the game starts or when spawned
void AStaircaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStaircaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStaircaseActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	DestroyAllChildrenComponents();

	for (int32 StepIndex = 0; StepIndex < NumberOfSteps; ++StepIndex)
	{
		CreateStepComponent(StepIndex);
	}

}

void AStaircaseActor::DestroyAllChildrenComponents()
{
	TArray<USceneComponent*> Childrens;
	RootComponent->GetChildrenComponents(true, Childrens);

	for (USceneComponent* Child : Childrens)
	{
		Child->DestroyComponent();
		Child = nullptr;
	}
}

void AStaircaseActor::CreateStepComponent(int32 StepIndex)
{
	FString MeshName = "MeshComponent" + FString::FromInt(StepIndex);
	UStaticMeshComponent* StepComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), *MeshName);
	if (StepComponent)
	{
		FVector StepLocation;
		FVector NewDimension;

		switch (TypeOfStair)
		{
		case EtypeOfStairs::openTypeStairs:
			StepLocation = FVector(((100 * 1 * StepIndex)), 0, (100 * StepIndex));
			
			break;
		case EtypeOfStairs::closeTypeStairs:
			StepLocation = FVector(((100 * 1 * StepIndex)), 0, (50 * StepIndex));
			break;
		case EtypeOfStairs::boxTypeStairs:
			UE_LOG(LogTemp, Warning, TEXT("Old position: %f, %f, %f"), StepLocation.X, StepLocation.Y, StepLocation.Z);
			UE_LOG(LogTemp, Warning, TEXT("Old dimension: %f, %f, %f"), StepDimension.X, StepDimension.Y, StepDimension.Z);
			StepLocation = FVector(100 * StepIndex, 0, 0);
			UE_LOG(LogTemp, Warning, TEXT("Steps and Indes: %f, %f, %f"), NumberOfSteps, StepIndex, StepLocation.Z);
			StepDimension = FVector(StepDimension.X , StepDimension.Y, StepDimension.X * (StepIndex + 1));
			UE_LOG(LogTemp, Warning, TEXT("new position: %f, %f, %f"), StepLocation.X, StepLocation.Y, StepLocation.Z);
			UE_LOG(LogTemp, Warning, TEXT("new dimension: %f, %f, %f"), StepDimension.X, StepDimension.Y, StepDimension.Z);
			break;
		}

		
		StepComponent->SetStaticMesh(StepMesh);
		StepComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		StepComponent->SetRelativeLocation(StepLocation);
		StepComponent->SetWorldScale3D(StepDimension);

		StepComponent->RegisterComponentWithWorld(GetWorld());
		CreateRailing(StepIndex , StepComponent);
	}
}

void AStaircaseActor::CreateRailing(int32 StepIndex , UStaticMeshComponent* _StepComponent)
{
	FVector ParentScale = _StepComponent->GetComponentScale();
	UStaticMeshComponent* LeftRailing = CreateRailingComponent("LeftRailing", StepIndex, FVector(0, -44, 100 ), _StepComponent);
	if (LeftRailing)
	{
		if (StepIndex == NumberOfSteps - 1)
		{
			//LeftRailing->SetRelativeLocation(FVector(0, -44, 100));
			LeftRailing->SetWorldScale3D(FVector(2.0f * ParentScale.X, 1.0f, RailingHeight / 100.0f));
		}
		else
		{
			LeftRailing->SetWorldScale3D(FVector(ParentScale.X / 6, 1.0f, RailingHeight / 100.0f));
		}
		
	}
	UStaticMeshComponent* RightRailing = CreateRailingComponent("RightRailing", StepIndex, FVector(0, 44, 100), _StepComponent);
	if (RightRailing)
	{
		
		if (StepIndex == NumberOfSteps - 1)
		{
			
			//RightRailing->SetRelativeLocation(FVector(0, 44, 100));
			RightRailing->SetWorldScale3D(FVector(ParentScale.X * 2, 1.0f, RailingHeight / 100.0f));

		}
		else {

			RightRailing->SetWorldScale3D(FVector(ParentScale.X / 6, 1.0f, RailingHeight / 100.0f));
		}
	}

}

void AStaircaseActor::CalculateRailingHandleRotation(UStaticMeshComponent* ComponentToAttach)
{
	if (RailingHandleMesh)
	{
		UStaticMeshComponent* RailingHandleComponent = NewObject<UStaticMeshComponent>(this);
		FVector ParentScale = ComponentToAttach->GetComponentScale();

		RailingHandleComponent->SetStaticMesh(RailingHandleMesh);
		RailingHandleComponent->SetWorldScale3D(ParentScale);

		
		FVector StepLocation = ComponentToAttach->GetComponentLocation();
		//StepLocation.Y = 0;
		//StepLocation.Z = RailingHeight;
		FVector HandleLocation = FVector(RailingHeight/2, 0, RailingHeight);/*FVector(0, 0, 0.2)*/
		RailingHandleComponent->AttachToComponent(ComponentToAttach, FAttachmentTransformRules::KeepRelativeTransform);
		RailingHandleComponent->SetRelativeLocation(StepLocation);
		//RailingHandleComponent->AddLocalRotation(FRotator(90,0,0));
		RailingHandleComponent->RegisterComponentWithWorld(GetWorld());
	}
}

UStaticMeshComponent* AStaircaseActor::CreateRailingComponent(const FString& ComponentName, int32 StepIndex, const FVector& RelativeLocation, UStaticMeshComponent* _StepComponent)
{
	UStaticMeshComponent* RailingComponent = NewObject<UStaticMeshComponent>(this);
	if (RailingComponent)
	{
		RailingComponent->SetStaticMesh(RailingMesh);
		RailingComponent->AttachToComponent(_StepComponent, FAttachmentTransformRules::KeepRelativeTransform);
		RailingComponent->SetRelativeLocation(RelativeLocation);
		RailingComponent->RegisterComponentWithWorld(GetWorld());
	}
	return RailingComponent;
}

//void AStaircaseActor::PreEditChange(FProperty* P)
//{
//	Super::PreEditChange(P); gzhsbbsbsbbshdhdhud
// d
// d
// d
// 
// d
// d
//}