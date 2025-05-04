// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/SceneComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��Ʈ ������Ʈ ����
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	// ī�޶� ������Ʈ ���� �� ��Ʈ�� ����
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	Camera->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (Camera)
	{
		PreviousCameraPosition = Camera->GetComponentLocation();
	}
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Camera)
	{
		return;
	}

	// ���� ī�޶� ��ġ
	FVector CurrentCameraPosition = Camera->GetComponentLocation();

	// ��ġ ��ȭ�� ���
	FVector MovementDelta = CurrentCameraPosition - PreviousCameraPosition;

	// ���� ���� (1.0�̸� ��ȭ ����, 2.0�̸� 2��)
	FVector ScaledDelta = MovementDelta * (SpeedMultiplier - 1.0f);

	// Pawn ��ü�� �ݴ� �������� �̵�
	AddActorWorldOffset(-ScaledDelta);

	// ���� ������ ��� ���� ��ġ ����
	PreviousCameraPosition = CurrentCameraPosition;
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

