#pragma once
#include "Module.h"
	class FastStop : public IModule {
public:
	FastStop();
	~FastStop();

	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	};
