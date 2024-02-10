#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Radio.generated.h"

class USoundCue;
class UAudioComponent;

UCLASS()
class WINTERROOM_API ARadio : public AActor
{
	GENERATED_BODY()
	
public:	
	ARadio();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RadioBody)
		UStaticMeshComponent* RadioBody;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RadioVars)
		USoundCue* RadioSound;

	UFUNCTION()
		void PlaySound();

protected:
	virtual void BeginPlay() override;

public:	
	UAudioComponent* ActionAudioComponent;
};