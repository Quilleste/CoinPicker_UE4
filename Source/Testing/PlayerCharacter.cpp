


#include "PlayerCharacter.h"

// init
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 86.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false; //no change in blueprints?

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 300.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	CameraFollow = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFollow"));
	CameraFollow->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraFollow->bUsePawnControlRotation = false; // no camera rotation relative to arm

	jumpHeight = 400.f;
	bIsDead = false;
	Power = 100.0f;
	TresholdPower = 2.f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);

	//create+attach a widget for hp
	if (PlayerPowerWidgetClass != nullptr) {
		PlayerPowerWidget = CreateWidget(GetWorld(), PlayerPowerWidgetClass);
		PlayerPowerWidget->AddToViewport();
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::doubleJump);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::moveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::moveRight);

}

void APlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	Power -= DeltaTime * TresholdPower;

	if (Power <= 0) {
		if (!bIsDead) {
			bIsDead = true;
			GetMesh()->SetSimulatePhysics(true);

			FTimerHandle timerHandle;
			GetWorldTimerManager().SetTimer(timerHandle, this, &APlayerCharacter::ResetGame, 4.f, false);
		}

	}
}

void APlayerCharacter::moveForward(float Axis)
{
	if (!bIsDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void APlayerCharacter::moveRight(float Axis)
{
	if (!bIsDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}

}

void APlayerCharacter::doubleJump()
{
	if (jumpValue <= 1) {
		ACharacter::LaunchCharacter(FVector(0, 0, jumpHeight), false, true);
		jumpValue++;
	}

}

void APlayerCharacter::ResetGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Coin")) {
		Power += 10.f;
		if (Power > 100.f) {
			Power = 100.f;
		}
		
		//bad practice. selfdestroy is preferable
		OtherActor->Destroy();
	}
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	jumpValue = 0;
}

