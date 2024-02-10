#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Types.h"
#include "Door.generated.h"

class USoundCue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDoorEvent, FString, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDoorAudioEvent, USoundCue*, Sound);

UCLASS()
class WINTERROOM_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DoorBody)
		UStaticMeshComponent* DoorFrame;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DoorBody)
		UBoxComponent* BoxArea;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DoorBody)
		UStaticMeshComponent* RollingSection;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FDoorEvent DoorEvent;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FDoorAudioEvent DoorAudioEvent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DoorVars)
		EKeyType KeyToUnlock;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DoorVars)
		USoundCue* DoorOpenSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DoorVars)
		USoundCue* DoorBlockedSound;

	void OpenDoor();
	void CheckToOpenDoor(TArray<EKeyType> Keys);

private:
	bool IsDoorOpen;

protected:
	virtual void BeginPlay() override;
};