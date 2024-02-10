#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Types.h"
#include "KeyPass.generated.h"

class USoundCue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKeyPassEvent, FString, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKeyPassAudioEvent, USoundCue*, Sound);

UCLASS()
class WINTERROOM_API AKeyPass : public AActor
{
	GENERATED_BODY()
	
public:	
	AKeyPass();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = KeyPass)
		UBoxComponent* KeyBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = KeyPass)
		UStaticMeshComponent* KeyBody;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = KeyPassVars)
		EKeyType KeyType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = KeyPassVars)
		USoundCue* KeySound;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FKeyPassEvent KeyPassEvent;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FKeyPassAudioEvent KeyPassAudioEvent;

protected:
	virtual void BeginPlay() override;

public:	
	EKeyType CatchKey();
};