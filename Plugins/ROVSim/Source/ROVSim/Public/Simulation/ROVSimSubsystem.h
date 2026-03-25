#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "ROVSimSubsystem.generated.h"

class AROVVehicle;

UCLASS()
class ROVSIM_API UROVSimSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void RegisterVehicle(AROVVehicle* Vehicle);
	void UnregisterVehicle(AROVVehicle* Vehicle);

	UFUNCTION(BlueprintCallable, Category = "ROV Simulation")
	void ResetSimulation();

	UFUNCTION(BlueprintPure, Category = "ROV Simulation")
	AROVVehicle* GetPrimaryVehicle() const;

	UFUNCTION(BlueprintPure, Category = "ROV Simulation")
	TArray<AROVVehicle*> GetVehicles() const;

private:
	void CompactVehicles();

	UPROPERTY(Transient)
	TArray<TObjectPtr<AROVVehicle>> RegisteredVehicles;
};
