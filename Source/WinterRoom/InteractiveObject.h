#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Types.h"
#include "InteractiveObject.generated.h"

class USoundCue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIOMessageEvent, FString, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractiveObjectEvent, bool, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIOAudioEvent, USoundCue*, Sound);

UCLASS()
class WINTERROOM_API AInteractiveObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractiveObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = IOBody)
		UStaticMeshComponent* ObjectBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = IOBody)
		UBoxComponent* BoxArea;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IOVars)
		EObjType ObjectRequired;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IOVars)
		USoundCue* ActionSound;

	void ManageAction();
	void CheckToExecuteAction(TArray<EObjType> Obj);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FIOMessageEvent IOMessageEvent;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FInteractiveObjectEvent IOBathroomEvent;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FInteractiveObjectEvent IOWallEvent;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FIOAudioEvent IOAudioEvent;

protected:
	virtual void BeginPlay() override;
};