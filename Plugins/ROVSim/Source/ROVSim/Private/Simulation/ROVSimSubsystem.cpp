#include "Simulation/ROVSimSubsystem.h"

#include "Simulation/ROVVehicle.h"

void UROVSimSubsystem::RegisterVehicle(AROVVehicle* Vehicle)
{
	if (!IsValid(Vehicle))
	{
		return;
	}

	CompactVehicles();
	RegisteredVehicles.AddUnique(Vehicle);
}

void UROVSimSubsystem::UnregisterVehicle(AROVVehicle* Vehicle)
{
	if (!Vehicle)
	{
		return;
	}

	RegisteredVehicles.RemoveSingleSwap(Vehicle);
}

void UROVSimSubsystem::ResetSimulation()
{
	CompactVehicles();

	for (AROVVehicle* Vehicle : RegisteredVehicles)
	{
		if (IsValid(Vehicle))
		{
			Vehicle->ResetVehicleState();
		}
	}
}

AROVVehicle* UROVSimSubsystem::GetPrimaryVehicle() const
{
	for (AROVVehicle* Vehicle : RegisteredVehicles)
	{
		if (IsValid(Vehicle))
		{
			return Vehicle;
		}
	}

	return nullptr;
}

TArray<AROVVehicle*> UROVSimSubsystem::GetVehicles() const
{
	TArray<AROVVehicle*> Vehicles;
	Vehicles.Reserve(RegisteredVehicles.Num());

	for (AROVVehicle* Vehicle : RegisteredVehicles)
	{
		if (IsValid(Vehicle))
		{
			Vehicles.Add(Vehicle);
		}
	}

	return Vehicles;
}

void UROVSimSubsystem::CompactVehicles()
{
	RegisteredVehicles.RemoveAll([](const TObjectPtr<AROVVehicle>& Vehicle)
	{
		return !IsValid(Vehicle);
	});
}
