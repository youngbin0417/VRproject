// MyPawn.cpp

#include "MyPawn.h"
#include "Components/SceneComponent.h"

// 생성자
AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// 루트 컴포넌트 설정
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// VROrigin 생성 및 루트에 부착
	VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	VROrigin->SetupAttachment(RootComponent);

	// Camera 생성 및 VROrigin에 부착
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	Camera->SetupAttachment(VROrigin);
}

// 게임 시작 시
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	if (Camera)
	{
		// VROrigin 기준 상대 위치 저장
		PreviousCameraPosition = Camera->GetRelativeLocation();
	}
}

// 매 프레임마다
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Camera || !VROrigin) return;

	// 현재 카메라 상대 위치 (VROrigin 기준)
	FVector CurrentCameraPosition = Camera->GetRelativeLocation();

	// 이동량 계산
	FVector MovementDelta = CurrentCameraPosition - PreviousCameraPosition;

	// 속도 배율 적용
	FVector ScaledDelta = MovementDelta * (SpeedMultiplier - 1.0f);

	// 기준점 이동 (플레이어가 멀리 이동한 것처럼 보이게 만듦)
	VROrigin->AddLocalOffset(-ScaledDelta);

	// 다음 프레임 대비 현재 위치 저장
	PreviousCameraPosition = CurrentCameraPosition;
}

// 입력 처리 (필요 시 확장)
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


