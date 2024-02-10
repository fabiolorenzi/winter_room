#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "CatchableObject.h"
#include "InteractiveObject.h"
#include "KeyPass.h"
#include "Types.h"

#include "PlayerCharacter.generated.h"

class USoundCue;
class UAudioComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPCPianoAudioEvent);

UCLASS()
class WINTERROOM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerVars)
		bool IsFlashlightOn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerVars)
		bool IsFlashlightActivable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerVars)
		bool IsPaused;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerVars)
	    FString TextMessage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerVars)
		TArray<EKeyType> Keys;
	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = PlayerVars)
		TArray<EObjType> Objects;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FPCPianoAudioEvent PCPianoEvent;
		
	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void OnRemovingBathroomCover(bool HasBeenOpened);
	UFUNCTION()
		void OnRemovingWallCover(bool HasBeenRemoved);
	UFUNCTION()
		void UpdateTextMessage(FString Value);
	UFUNCTION()
		void PlayActionSound(USoundCue* Sound);

	float FlashlightPower;
	bool HasPassedNearThePiano;
	bool HasNearPianoAudioEffectBeenPlayed;

	void ResetTextMessage();
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void ManageAction();
	void ManageFlashlight();
	void PauseGame();
	void RestartGame();
	void QuitGame();

private:
	bool IsOverlapping;
	AActor* OverlappedObject;

	bool HasPlayerOpenBathtub;
	bool HasPlayerRemovedWallCover;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UAudioComponent* ActionAudioComponent;
};