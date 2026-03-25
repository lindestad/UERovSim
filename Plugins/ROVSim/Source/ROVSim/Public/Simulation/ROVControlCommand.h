#pragma once

#include "CoreMinimal.h"

#include "ROVControlCommand.generated.h"

USTRUCT(BlueprintType)
struct ROVSIM_API FROVControlCommand
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ROV Control")
	FVector Linear = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ROV Control")
	FVector Angular = FVector::ZeroVector;

	void Reset()
	{
		Linear = FVector::ZeroVector;
		Angular = FVector::ZeroVector;
	}
};
