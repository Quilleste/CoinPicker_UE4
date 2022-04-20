// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Blueprint/UserWidget.h"
//restart
#include "Kismet/GameplayStatics.h"

#include "PlayerCharacter.generated.h"

UCLASS(BlueprintType)
class TESTING_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* CameraFollow;
	
	//double jump functionality
	//might be also realised through JumpMaxCount?
	UPROPERTY()
		int jumpValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float jumpHeight;

	UPROPERTY()
		bool bIsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Power;
	UPROPERTY(EditAnywhere)
		float TresholdPower;

	UPROPERTY(EditAnywhere, Category = "UI Display")
		TSubclassOf<UUserWidget> PlayerPowerWidgetClass;
	UUserWidget* PlayerPowerWidget;


		

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
		void moveForward(float Axis);
	UFUNCTION()
		void moveRight(float Axis);

	UFUNCTION()
		void doubleJump();

	void ResetGame();

	//overlap functionality
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Landed(const FHitResult& Hit) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

};
