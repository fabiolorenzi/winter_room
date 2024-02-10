#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Types.h"
#include "CatchableObject.generated.h"

class USoundCue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCOEvent, FString, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCOAudioEvent, USoundCue*, Sound);

UCLASS()
class WINTERROOM_API ACatchableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ACatchableObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CatchableObject)
		UBoxComponent* ObjectBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CatchableObject)
		UStaticMeshComponent* ObjectBody;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ObjectVars)
		EObjType ObjectType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ObjectVars)
		USoundCue* CatchSound;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FCOEvent COEvent;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FCOAudioEvent COAudioEvent;

protected:
	virtual void BeginPlay() override;

public:	
	EObjType CatchObject();
};