// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class VRSPEED_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// HMD 위치 추적용 카메라 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	UCameraComponent* Camera;

	// 속도 왜곡 배율 (1.0 = 기본, 2.0 = 2배 빠르게 이동)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Walking Distortion")
	float SpeedMultiplier = 1.0f;

private:
	// 이전 프레임 카메라 위치 저장
	FVector PreviousCameraPosition;

};
