#include "Radio.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#include "PlayerCharacter.h"

ARadio::ARadio()
{
	PrimaryActorTick.bCanEverTick = true;

	RadioBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RadioBody"));
	RadioBody->SetupAttachment(RootComponent);
}

void ARadio::PlaySound()
{
	ActionAudioComponent = UGameplayStatics::SpawnSound2D(this, RadioSound, 1.0f);
}

void ARadio::BeginPlay()
{
	Super::BeginPlay();
	Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->PCRadioEvent.AddDynamic(this, &ARadio::PlaySound);
}