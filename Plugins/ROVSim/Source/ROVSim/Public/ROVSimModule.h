#pragma once

#include "Modules/ModuleInterface.h"

class FROVSimModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
