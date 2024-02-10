#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "DiningRoomSound.generated.h"

class USoundCue;
class UAudioComponent;

UCLASS()
class WINTERROOM_API ADiningRoomSound : public AActor
{
	GENERATED_BODY()
	
public:	
	ADiningRoomSound();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DRSBody)
		UStaticMeshComponent* DNSBody;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DRSVars)
		USoundCue* DNSSound;

	UFUNCTION()
		void PlaySound();

protected:
	virtual void BeginPlay() override;

public:	
	UAudioComponent* ActionAudioComponent;
};