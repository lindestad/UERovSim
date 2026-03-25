#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Simulation/ROVControlCommand.h"

#include "ROVVehicle.generated.h"

class UROVSimSubsystem;
class UROVThrusterComponent;
class UStaticMeshComponent;

UCLASS(Blueprintable)
class ROVSIM_API AROVVehicle : public AActor
{
	GENERATED_BODY()

public:
	AROVVehicle();

	virtual void Tick(float DeltaSeconds) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable, Category = "ROV Vehicle")
	void SetControlCommand(const FROVControlCommand& NewCommand);

	UFUNCTION(BlueprintPure, Category = "ROV Vehicle")
	FROVControlCommand GetControlCommand() const;

	UFUNCTION(BlueprintCallable, Category = "ROV Vehicle")
	void ResetVehicleState();

	UFUNCTION(BlueprintPure, Category = "ROV Vehicle")
	UStaticMeshComponent* GetVehicleBody() const;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ROV Vehicle")
	TObjectPtr<UStaticMeshComponent> VehicleBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ROV Vehicle")
	bool bAutoRegisterWithSubsystem = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ROV Vehicle")
	FROVControlCommand ControlCommand;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "ROV Vehicle")
	TArray<TObjectPtr<UROVThrusterComponent>> Thrusters;

private:
	void RefreshThrusters();
	void ApplyThrusters() const;
	void RegisterWithSubsystem();
	void UnregisterFromSubsystem();

	FTransform InitialTransform = FTransform::Identity;
};
