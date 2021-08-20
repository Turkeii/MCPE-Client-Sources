#pragma once
#include "Module.h"
class EditionFaker : public IModule {
public:
	EditionFaker();
	~EditionFaker();

	bool RandomEdition = true;
	int turn = 0;
	int edition = 1;

	int getFakedEditon();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
};
