#include "Piano.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

#include "PlayerCharacter.h"

APiano::APiano()
{
	PrimaryActorTick.bCanEverTick = true;

	PianoBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PianoBody"));
	PianoBody->SetupAttachment(RootComponent);
}

void APiano::PlaySound()
{
	UGameplayStatics::PlaySoundAtLocation(this, PianoSound, FVector(-362.0f, -1067.0f, -193.0f), 1.0f);
}

void APiano::BeginPlay()
{
	Super::BeginPlay();
	Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->PCPianoEvent.AddDynamic(this, &APiano::PlaySound);
}