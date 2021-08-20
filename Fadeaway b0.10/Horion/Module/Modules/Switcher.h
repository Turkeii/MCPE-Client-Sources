#include "Module.h"

class Switcher : public IModule {
private:
	int ternary = false;
	int ternary1 = false;

public:
	Switcher();
	~Switcher();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onAttack(C_Entity* attackedEnt) override;
};
