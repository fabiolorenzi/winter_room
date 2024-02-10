#include "DiningRoomSound.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#include "PlayerCharacter.h"

ADiningRoomSound::ADiningRoomSound()
{
	PrimaryActorTick.bCanEverTick = true;

	DNSBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DNSBody"));
	DNSBody->SetupAttachment(RootComponent);
}

void ADiningRoomSound::PlaySound()
{
	ActionAudioComponent = UGameplayStatics::SpawnSound2D(this, DNSSound, 1.0f);
}

void ADiningRoomSound::BeginPlay()
{
	Super::BeginPlay();
	Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->PCDNSEvent.AddDynamic(this, &ADiningRoomSound::PlaySound);
}