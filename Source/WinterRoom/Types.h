#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EKeyType: uint8 {
	NoKey = 0,
	ZeroFloorUnderground = 1,
	ZeroFloorDiningRoom = 2,
	ZeroFloorCorridor = 3,
	ZeroFloorTopFloorCorridor = 4,
	TopFloorBathRoom = 5,
	TopFloorRoomOne = 6,
	TopFloorRoomTwo = 7,
	Exit = 8
};

UENUM(BlueprintType)
enum class EObjType: uint8 {
	NoObject = 0,
	Hammer = 1,
	Crowbar = 2,
	Handle = 3
};

class WINTERROOM_API Types
{
public:
	Types();
	~Types();
};
