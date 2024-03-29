#include "Radio.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

#include "PlayerCharacter.h"

ARadio::ARadio()
{
	PrimaryActorTick.bCanEverTick = true;

	RadioBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RadioBody"));
	RadioBody->SetupAttachment(RootComponent);
}

void ARadio::PlaySound()
{
	UGameplayStatics::PlaySoundAtLocation(this, RadioSound, FVector(-489.0f, -1551.0f, 417.0f), 1.0f);
}

void ARadio::BeginPlay()
{
	Super::BeginPlay();
	Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->PCRadioEvent.AddDynamic(this, &ARadio::PlaySound);
}