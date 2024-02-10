#include "Piano.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#include "PlayerCharacter.h"

APiano::APiano()
{
	PrimaryActorTick.bCanEverTick = true;

	PianoBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PianoBody"));
	PianoBody->SetupAttachment(RootComponent);
}

void APiano::PlaySound()
{
	ActionAudioComponent = UGameplayStatics::SpawnSound2D(this, PianoSound, 1.0f);
}

void APiano::BeginPlay()
{
	Super::BeginPlay();
	Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->PCPianoEvent.AddDynamic(this, &APiano::PlaySound);
}