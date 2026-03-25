#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Simulation/ROVControlCommand.h"

#include "ROVThrusterComponent.generated.h"

class UPrimitiveComponent;

UCLASS(ClassGroup = (ROVSim), meta = (BlueprintSpawnableComponent))
class ROVSIM_API UROVThrusterComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UROVThrusterComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thruster")
	float MaxForce = 2500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thruster")
	FVector LinearContribution = FVector::ForwardVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thruster")
	FVector AngularContribution = FVector::ZeroVector;

	UFUNCTION(BlueprintCallable, Category = "Thruster")
	float GetThrottleForCommand(const FROVControlCommand& Command) const;

	UFUNCTION(BlueprintCallable, Category = "Thruster")
	void ApplyControlCommand(const FROVControlCommand& Command, UPrimitiveComponent* TargetBody) const;
};
