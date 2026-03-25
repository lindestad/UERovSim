#include "Simulation/ROVThrusterComponent.h"

#include "Components/PrimitiveComponent.h"

UROVThrusterComponent::UROVThrusterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UROVThrusterComponent::GetThrottleForCommand(const FROVControlCommand& Command) const
{
	const FVector LinearInput = Command.Linear.GetClampedToMaxSize(1.0f);
	const FVector AngularInput = Command.Angular.GetClampedToMaxSize(1.0f);

	const float LinearDemand = FVector::DotProduct(LinearInput, LinearContribution);
	const float AngularDemand = FVector::DotProduct(AngularInput, AngularContribution);

	return FMath::Clamp(LinearDemand + AngularDemand, -1.0f, 1.0f);
}

void UROVThrusterComponent::ApplyControlCommand(const FROVControlCommand& Command, UPrimitiveComponent* TargetBody) const
{
	if (!TargetBody || !TargetBody->IsSimulatingPhysics())
	{
		return;
	}

	const float Throttle = GetThrottleForCommand(Command);
	if (FMath::IsNearlyZero(Throttle))
	{
		return;
	}

	const FVector Force = GetForwardVector() * (Throttle * MaxForce);
	TargetBody->AddForceAtLocation(Force, GetComponentLocation());
}
