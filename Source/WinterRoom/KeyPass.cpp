#include "KeyPass.h"
#include "Types.h"

AKeyPass::AKeyPass()
{
	PrimaryActorTick.bCanEverTick = true;

	KeyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyBox"));
	KeyBox->SetupAttachment(RootComponent);

	KeyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyBody"));
	KeyBody->SetupAttachment(KeyBox);
}

void AKeyPass::BeginPlay()
{
	Super::BeginPlay();
}

EKeyType AKeyPass::CatchKey()
{
	switch (KeyType) {
		case EKeyType::ZeroFloorUnderground:
			KeyPassEvent.Broadcast("Catched key for underground storage");
			break;
		case EKeyType::ZeroFloorDiningRoom:
			KeyPassEvent.Broadcast("Catched key for dining room");
			break;
		case EKeyType::ZeroFloorCorridor:
			KeyPassEvent.Broadcast("Catched key for main corridor");
			break;
		case EKeyType::ZeroFloorTopFloorCorridor:
			KeyPassEvent.Broadcast("Catched key for top floor");
			break;
		case EKeyType::TopFloorBathRoom:
			KeyPassEvent.Broadcast("Catched key for top bathroom");
			break;
		case EKeyType::TopFloorRoomOne:
			KeyPassEvent.Broadcast("Catched key for small room");
			break;
		case EKeyType::TopFloorRoomTwo:
			KeyPassEvent.Broadcast("Catched key for big room");
			break;
		case EKeyType::Exit:
			KeyPassEvent.Broadcast("Catched key for main door");
			break;
	};
	KeyPassAudioEvent.Broadcast(KeySound);

	return KeyType;
}