#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Piano.generated.h"

class USoundCue;

UCLASS()
class WINTERROOM_API APiano : public AActor
{
	GENERATED_BODY()
	
public:	
	APiano();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PianoBody)
		UStaticMeshComponent* PianoBody;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PianoVars)
		USoundCue* PianoSound;

	UFUNCTION()
		void PlaySound();

protected:
	virtual void BeginPlay() override;
};