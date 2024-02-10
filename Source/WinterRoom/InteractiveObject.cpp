#include "InteractiveObject.h"

AInteractiveObject::AInteractiveObject()
{
	PrimaryActorTick.bCanEverTick = true;

	ObjectBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectBody"));
	ObjectBody->SetupAttachment(RootComponent);

	BoxArea = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxArea"));
	BoxArea->SetupAttachment(ObjectBody);
}

void AInteractiveObject::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractiveObject::ManageAction()
{
	if (ObjectRequired == EObjType::Handle) {
		IOBathroomEvent.Broadcast(true);
	} else if (ObjectRequired == EObjType::Crowbar) {
		IOWallEvent.Broadcast(true);
	};
	IOAudioEvent.Broadcast(ActionSound);
	Destroy();
}

void AInteractiveObject::CheckToExecuteAction(TArray<EObjType> Obj)
{
	if (Obj.Contains(ObjectRequired)) {
		ManageAction();
	} else {
		if (ObjectRequired == EObjType::Hammer) {
			IOMessageEvent.Broadcast("You need something like a hammer to break this wall");
		} else if (ObjectRequired == EObjType::Crowbar) {
			IOMessageEvent.Broadcast("You need something like a crowbar to move this cover");
		} else if (ObjectRequired == EObjType::Handle) {
			IOMessageEvent.Broadcast("You need something like a handle to open the bathtub");
		};
	};
}