// Fill out your copyright notice in the Description page of Project Settings.


#include "AFirstPersonPawn.h"
#include "PawnController.h"		
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFrameWork/FloatingPawnMovement.h"
#include "InputMappingContext.h"

static void KeyMap(UInputMappingContext* InputMappingContext, UInputAction* InputAction, FKey Key, bool bNegate = false
	, bool bSwizzle = false, EInputAxisSwizzle SwizzeleOrder = EInputAxisSwizzle::YXZ)
{

	auto& Mapping = InputMappingContext->MapKey(InputAction, Key);
	auto* Outer = InputMappingContext->GetOuter();
	if (bNegate)
	{
		auto* Negate = NewObject<UInputModifierNegate>(Outer);
		Mapping.Modifiers.Add(Negate);
	}
	if (bSwizzle)
	{
		auto* Swizzle = NewObject<UInputModifierSwizzleAxis>(Outer);
		Swizzle->Order = SwizzeleOrder;
		Mapping.Modifiers.Add(Swizzle);
	}
}
// Sets default values
AAFirstPersonPawn::AAFirstPersonPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	RootComponent = CameraComponent;
	pMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	MoveScale = 1.0f;
	RotateScale = 50.f;

	PawnAttributes=LoadObject<UPawnAttributeAsset>(nullptr, TEXT("/Script/Assigment1_2.PawnAttributeAsset'/Game/DataAssert/DA_FirstPerson.DA_FirstPerson'"));
		
}

// Called when the game starts or when spawned
void AAFirstPersonPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAFirstPersonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAFirstPersonPawn::MoveForward(float Value)
{
	FVector MovementDirection = FVector::ZeroVector;

	if (Controller != nullptr)
	{
		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	
		MovementDirection = ForwardDirection * Value;
	}


	AddMovementInput(MovementDirection);
}


void AAFirstPersonPawn::Move(const FInputActionValue& ActionValue)
{
	FVector Input = ActionValue.Get<FVector>();
	AddMovementInput(GetActorRotation().RotateVector(Input), MoveScale);
}

void AAFirstPersonPawn::Rotate(const FInputActionValue& ActionValue)
{
	FRotator Input(ActionValue[0], ActionValue[1], ActionValue[2]);
	Input *= GetWorld()->GetDeltaSeconds() * RotateScale;
	Input += GetActorRotation();
	Input.Pitch = FMath::ClampAngle(Input.Pitch, -89.9f, 89.9f);
	Input.Roll = 0;
	SetActorRotation(Input);
}


void AAFirstPersonPawn::LookUp(float Value)
{
	
}

void AAFirstPersonPawn::LookRight(float Value)
{
	
}
void AAFirstPersonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PawnMappingContext = NewObject<UInputMappingContext>(this);
	 
	MoveAction = NewObject<UInputAction>(this);
	MoveAction->ValueType = EInputActionValueType::Axis3D;
	KeyMap(PawnMappingContext, MoveAction, EKeys::W);
	KeyMap(PawnMappingContext, MoveAction, EKeys::S, true);
	KeyMap(PawnMappingContext, MoveAction, EKeys::A, true, true);
	KeyMap(PawnMappingContext, MoveAction, EKeys::D, false, true);
	KeyMap(PawnMappingContext, MoveAction, EKeys::Q, true, true, EInputAxisSwizzle::ZYX);
	KeyMap(PawnMappingContext, MoveAction, EKeys::E, false, true, EInputAxisSwizzle::ZYX);

	RotateAction = NewObject<UInputAction>(this);
	RotateAction->ValueType = EInputActionValueType::Axis2D;

	KeyMap(PawnMappingContext, RotateAction, EKeys::MouseY);
	KeyMap(PawnMappingContext, RotateAction, EKeys::MouseX, false, true);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	APlayerController* FPC = Cast<APlayerController>(Controller);

	check(EIC && FPC);

	EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAFirstPersonPawn::Move);
	EIC->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AAFirstPersonPawn::Rotate);
	ULocalPlayer* LocalPlayer = FPC->GetLocalPlayer();
	check(LocalPlayer);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PawnMappingContext, 0);
}

