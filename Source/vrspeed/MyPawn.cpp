// MyPawn.cpp

#include "MyPawn.h"
#include "Components/SceneComponent.h"

// ������
AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// ��Ʈ ������Ʈ ����
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// VROrigin ���� �� ��Ʈ�� ����
	VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	VROrigin->SetupAttachment(RootComponent);

	// Camera ���� �� VROrigin�� ����
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	Camera->SetupAttachment(VROrigin);
}

// ���� ���� ��
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	if (Camera)
	{
		// VROrigin ���� ��� ��ġ ����
		PreviousCameraPosition = Camera->GetRelativeLocation();
	}
}

// �� �����Ӹ���
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Camera || !VROrigin) return;

	// ���� ī�޶� ��� ��ġ (VROrigin ����)
	FVector CurrentCameraPosition = Camera->GetRelativeLocation();

	// �̵��� ���
	FVector MovementDelta = CurrentCameraPosition - PreviousCameraPosition;

	// �ӵ� ���� ����
	FVector ScaledDelta = MovementDelta * (SpeedMultiplier - 1.0f);

	// ������ �̵� (�÷��̾ �ָ� �̵��� ��ó�� ���̰� ����)
	VROrigin->AddLocalOffset(-ScaledDelta);

	// ���� ������ ��� ���� ��ġ ����
	PreviousCameraPosition = CurrentCameraPosition;
}

// �Է� ó�� (�ʿ� �� Ȯ��)
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


