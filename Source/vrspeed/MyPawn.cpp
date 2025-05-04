// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/SceneComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 루트 컴포넌트 생성
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	// 카메라 컴포넌트 생성 및 루트에 부착
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

	// 현재 카메라 위치
	FVector CurrentCameraPosition = Camera->GetComponentLocation();

	// 위치 변화량 계산
	FVector MovementDelta = CurrentCameraPosition - PreviousCameraPosition;

	// 배율 적용 (1.0이면 변화 없음, 2.0이면 2배)
	FVector ScaledDelta = MovementDelta * (SpeedMultiplier - 1.0f);

	// Pawn 자체를 반대 방향으로 이동
	AddActorWorldOffset(-ScaledDelta);

	// 다음 프레임 대비 현재 위치 저장
	PreviousCameraPosition = CurrentCameraPosition;
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

