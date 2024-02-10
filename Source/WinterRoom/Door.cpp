#include "Door.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(RootComponent);

	BoxArea = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxArea"));
	BoxArea->SetupAttachment(DoorFrame);

	RollingSection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RollingSection"));
	RollingSection->SetupAttachment(DoorFrame);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	if (KeyToUnlock == EKeyType::NoKey) {
		OpenDoor();
	} else {
		IsDoorOpen = false;
	};
}

void ADoor::OpenDoor()
{
	IsDoorOpen = true;
	FRotator DoorRotation = RollingSection->GetRelativeRotation();
	DoorRotation.Yaw += 90.0f;
	RollingSection->SetRelativeRotation(DoorRotation);
	DoorAudioEvent.Broadcast(DoorOpenSound);
}

void ADoor::CheckToOpenDoor(TArray<EKeyType> Keys)
{
	if (!IsDoorOpen) {
		if (Keys.Contains(KeyToUnlock)) {
			OpenDoor();
		} else {
			DoorAudioEvent.Broadcast(DoorBlockedSound);
			DoorEvent.Broadcast("You need the right key to unlock this door");
		};
	};
}