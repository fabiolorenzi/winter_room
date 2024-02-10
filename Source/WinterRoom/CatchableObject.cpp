#include "CatchableObject.h"
#include "Types.h"

ACatchableObject::ACatchableObject()
{
	PrimaryActorTick.bCanEverTick = true;

	ObjectBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ObjectBox"));
	ObjectBox->SetupAttachment(RootComponent);

	ObjectBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectBody"));
	ObjectBody->SetupAttachment(ObjectBox);
}

void ACatchableObject::BeginPlay()
{
	Super::BeginPlay();
}

EObjType ACatchableObject::CatchObject()
{
	COAudioEvent.Broadcast(CatchSound);
	switch (ObjectType) {
		case EObjType::Hammer:
			COEvent.Broadcast("Catched hammer");
			break;
		case EObjType::Crowbar:
			COEvent.Broadcast("Catched crowbar");
			break;
		case EObjType::Handle:
			COEvent.Broadcast("Catched handle");
			break;
	};

	return(ObjectType);
}