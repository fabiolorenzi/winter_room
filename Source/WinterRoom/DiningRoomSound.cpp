#include "DiningRoomSound.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

#include "PlayerCharacter.h"

ADiningRoomSound::ADiningRoomSound()
{
	PrimaryActorTick.bCanEverTick = true;

	DNSBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DNSBody"));
	DNSBody->SetupAttachment(RootComponent);
}

void ADiningRoomSound::PlaySound()
{
	UGameplayStatics::PlaySoundAtLocation(this, DNSSound, FVector((-900.0f, -1312.0f, 44.0f)), 1.0f);
}

void ADiningRoomSound::BeginPlay()
{
	Super::BeginPlay();
	Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->PCDNSEvent.AddDynamic(this, &ADiningRoomSound::PlaySound);
}