#include "Simulation/ROVVehicle.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/World.h"
#include "Simulation/ROVSimSubsystem.h"
#include "Simulation/ROVThrusterComponent.h"

AROVVehicle::AROVVehicle()
{
	PrimaryActorTick.bCanEverTick = true;

	VehicleBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleBody"));
	SetRootComponent(VehicleBody);

	VehicleBody->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	VehicleBody->SetSimulatePhysics(true);
	VehicleBody->SetEnableGravity(false);
	VehicleBody->SetLinearDamping(0.4f);
	VehicleBody->SetAngularDamping(1.0f);
}

void AROVVehicle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ApplyThrusters();
}

void AROVVehicle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	RefreshThrusters();
}

void AROVVehicle::SetControlCommand(const FROVControlCommand& NewCommand)
{
	ControlCommand = NewCommand;
}

FROVControlCommand AROVVehicle::GetControlCommand() const
{
	return ControlCommand;
}

void AROVVehicle::ResetVehicleState()
{
	SetActorTransform(InitialTransform, false, nullptr, ETeleportType::TeleportPhysics);

	if (VehicleBody)
	{
		VehicleBody->SetPhysicsLinearVelocity(FVector::ZeroVector);
		VehicleBody->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	}

	ControlCommand.Reset();
}

UStaticMeshComponent* AROVVehicle::GetVehicleBody() const
{
	return VehicleBody;
}

void AROVVehicle::BeginPlay()
{
	Super::BeginPlay();

	InitialTransform = GetActorTransform();
	RefreshThrusters();

	if (bAutoRegisterWithSubsystem)
	{
		RegisterWithSubsystem();
	}
}

void AROVVehicle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterFromSubsystem();

	Super::EndPlay(EndPlayReason);
}

void AROVVehicle::RefreshThrusters()
{
	TArray<UROVThrusterComponent*> FoundThrusters;
	GetComponents<UROVThrusterComponent>(FoundThrusters);

	Thrusters.Reset();
	for (UROVThrusterComponent* Thruster : FoundThrusters)
	{
		Thrusters.Add(Thruster);
	}
}

void AROVVehicle::ApplyThrusters() const
{
	if (!VehicleBody || !VehicleBody->IsSimulatingPhysics())
	{
		return;
	}

	for (const UROVThrusterComponent* Thruster : Thrusters)
	{
		if (IsValid(Thruster))
		{
			Thruster->ApplyControlCommand(ControlCommand, VehicleBody);
		}
	}
}

void AROVVehicle::RegisterWithSubsystem()
{
	if (UWorld* World = GetWorld())
	{
		if (UROVSimSubsystem* Subsystem = World->GetSubsystem<UROVSimSubsystem>())
		{
			Subsystem->RegisterVehicle(this);
		}
	}
}

void AROVVehicle::UnregisterFromSubsystem()
{
	if (UWorld* World = GetWorld())
	{
		if (UROVSimSubsystem* Subsystem = World->GetSubsystem<UROVSimSubsystem>())
		{
			Subsystem->UnregisterVehicle(this);
		}
	}
}
