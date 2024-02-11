#include "PlayerCharacter.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#include "Door.h"
#include "InteractiveObject.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 20.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollorCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = true;

	IsPaused = false;
	IsGameFinished = false;
	IsFlashlightOn = false;
	IsFlashlightActivable = true;
	FlashlightPower = 100.0f;
	HasPassedNearThePiano = false;
	HasNearPianoAudioEffectBeenPlayed = false;
	HasPassedNearDiningRoom = false;
	HasPassedNearTheRadio = false;
	HasNearRadioAudioEffectBeenPlayed = false;
	IsOverlapping = false;
	HasPlayerOpenBathtub = false;
	HasPlayerRemovedWallCover = false;
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &Sweep)
{
	if (OtherActor->ActorHasTag("Door") || OtherActor->ActorHasTag("KeyPass") || OtherActor->ActorHasTag("CatchableObject") || OtherActor->ActorHasTag("InteractiveObject")) {
		IsOverlapping = true;
		OverlappedObject = OtherActor;
        if (OverlappedObject->ActorHasTag("BathtubCover")) {
			Cast<AInteractiveObject>(OverlappedObject)->IOBathroomEvent.AddDynamic(this, &APlayerCharacter::OnRemovingBathroomCover);
		} else if (OverlappedObject->ActorHasTag("WallCover")) {
			Cast<AInteractiveObject>(OverlappedObject)->IOWallEvent.AddDynamic(this, &APlayerCharacter::OnRemovingWallCover);
		};
	} else if (OtherActor->ActorHasTag("NearPiano")) {
		HasPassedNearThePiano = true;
	} else if (OtherActor->ActorHasTag("NearPianoExit") && HasPassedNearThePiano && !HasNearPianoAudioEffectBeenPlayed) {
		HasNearPianoAudioEffectBeenPlayed = true;
		PCPianoEvent.Broadcast();
	} else if (OtherActor->ActorHasTag("DiningRoomPassing") && !HasPassedNearDiningRoom) {
		HasPassedNearDiningRoom = true;
		PCDNSEvent.Broadcast();
	} else if (OtherActor->ActorHasTag("NearRadio")) {
		HasPassedNearTheRadio = true;
	} else if (OtherActor->ActorHasTag("NearRadioExit") && HasPassedNearTheRadio && !HasNearRadioAudioEffectBeenPlayed) {
		HasNearRadioAudioEffectBeenPlayed = true;
		PCRadioEvent.Broadcast();
	} else {
		IsOverlapping = false;
		OverlappedObject = nullptr;
	};
}

void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IsOverlapping = false;
	OverlappedObject = nullptr;
}

void APlayerCharacter::OnRemovingBathroomCover(bool HasBeenOpened)
{
	HasPlayerOpenBathtub = true;
}

void APlayerCharacter::OnRemovingWallCover(bool HasBeenRemoved)
{
	HasPlayerRemovedWallCover = true;
}

void APlayerCharacter::UpdateTextMessage(FString Value)
{
	TextMessage = Value;

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerCharacter::ResetTextMessage, 3.0f, false);
}

void APlayerCharacter::ResetTextMessage()
{
	TextMessage = "";
}

void APlayerCharacter::PlayActionSound(USoundCue* Sound)
{
	ActionAudioComponent = UGameplayStatics::SpawnSound2D(this, Sound, 1.0f);
}

void APlayerCharacter::EndGame()
{
	PauseGame();
	IsGameFinished = true;
}

void APlayerCharacter::MoveForward(float Axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Axis);
}

void APlayerCharacter::MoveRight(float Axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);
}

void APlayerCharacter::ManageAction()
{
	if (IsOverlapping) {
		if (OverlappedObject->ActorHasTag("KeyPass") && OverlappedObject->ActorHasTag("BathtubKeyPass") == false) {
			Cast<AKeyPass>(OverlappedObject)->KeyPassEvent.AddDynamic(this, &APlayerCharacter::UpdateTextMessage);
			Cast<AKeyPass>(OverlappedObject)->KeyPassAudioEvent.AddDynamic(this, &APlayerCharacter::PlayActionSound);
			Keys.Add(Cast<AKeyPass>(OverlappedObject)->CatchKey());
			OverlappedObject->Destroy();
		} else if (OverlappedObject->ActorHasTag("BathtubKeyPass")) {
			if (HasPlayerOpenBathtub) {
				Cast<AKeyPass>(OverlappedObject)->KeyPassEvent.AddDynamic(this, &APlayerCharacter::UpdateTextMessage);
				Cast<AKeyPass>(OverlappedObject)->KeyPassAudioEvent.AddDynamic(this, &APlayerCharacter::PlayActionSound);
				Keys.Add(Cast<AKeyPass>(OverlappedObject)->CatchKey());
				OverlappedObject->Destroy();
			};
		} else if (OverlappedObject->ActorHasTag("Door")) {
			Cast<ADoor>(OverlappedObject)->DoorEvent.AddDynamic(this, &APlayerCharacter::UpdateTextMessage);
			Cast<ADoor>(OverlappedObject)->DoorAudioEvent.AddDynamic(this, &APlayerCharacter::PlayActionSound);
			if (OverlappedObject->ActorHasTag("ExitDoor")) {
				Cast<ADoor>(OverlappedObject)->DoorExitEvent.AddDynamic(this, &APlayerCharacter::EndGame);
			};
			Cast<ADoor>(OverlappedObject)->CheckToOpenDoor(Keys);
		} else if (OverlappedObject->ActorHasTag("InteractiveObject")) {
			Cast<AInteractiveObject>(OverlappedObject)->IOMessageEvent.AddDynamic(this, &APlayerCharacter::UpdateTextMessage);
			Cast<AInteractiveObject>(OverlappedObject)->IOAudioEvent.AddDynamic(this, &APlayerCharacter::PlayActionSound);
			if (OverlappedObject->ActorHasTag("BlockingWall")) {
				if (HasPlayerRemovedWallCover) {
					Cast<AInteractiveObject>(OverlappedObject)->CheckToExecuteAction(Objects);
				};
			} else {
				Cast<AInteractiveObject>(OverlappedObject)->CheckToExecuteAction(Objects);
			};
		} else if (OverlappedObject->ActorHasTag("CatchableObject")) {
			Cast<ACatchableObject>(OverlappedObject)->COEvent.AddDynamic(this, &APlayerCharacter::UpdateTextMessage);
			Cast<ACatchableObject>(OverlappedObject)->COAudioEvent.AddDynamic(this, &APlayerCharacter::PlayActionSound);
			Objects.Add(Cast<ACatchableObject>(OverlappedObject)->CatchObject());
			OverlappedObject->Destroy();
		};
	};
}

void APlayerCharacter::ManageFlashlight()
{
	if (IsFlashlightActivable) {
		IsFlashlightOn = !IsFlashlightOn;
	};
}

void APlayerCharacter::RestartGame()
{
	if (IsPaused) {
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	};
}

void APlayerCharacter::QuitGame()
{
	if (IsPaused) {
		FGenericPlatformMisc::RequestExit(false);
	};
}

void APlayerCharacter::PauseGame()
{
	if (!IsGameFinished) {
		IsPaused = !IsPaused;

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		PlayerController->Pause();
		PlayerController->bShowMouseCursor = IsPaused;
		PlayerController->bEnableClickEvents = IsPaused;
	};
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEnd);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsFlashlightOn) {
		FlashlightPower -= 2.0f * DeltaTime;
	} else if (FlashlightPower <= 100.0f) {
		FlashlightPower += 0.5f * DeltaTime;
	};

	if (FlashlightPower <= 0.0f) {
		IsFlashlightOn = false;
		IsFlashlightActivable = false;
	};

	if (FlashlightPower >= 20.0f && !IsFlashlightActivable) {
		IsFlashlightActivable = true;
	};
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &APlayerCharacter::ManageAction);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerCharacter::PauseGame).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("RestartGame", IE_Pressed, this, &APlayerCharacter::RestartGame).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("QuitGame", IE_Pressed, this, &APlayerCharacter::QuitGame).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("Flashlight", IE_Pressed, this, &APlayerCharacter::ManageFlashlight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
}