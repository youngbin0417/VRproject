// MyPawn.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "MyPawn.generated.h"

UCLASS()
class VRSPEED_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 플레이어 기준점 (룸스케일 트래킹용)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	USceneComponent* VROrigin;

	// HMD 위치를 따르는 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	UCameraComponent* Camera;

	// 속도 왜곡 배율 (1.0 = 기본, 2.0 = 2배 빠르게 이동)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Walking Distortion")
	float SpeedMultiplier = 1.0f;

private:
	// 이전 프레임 카메라 상대 위치 저장
	FVector PreviousCameraPosition;
};