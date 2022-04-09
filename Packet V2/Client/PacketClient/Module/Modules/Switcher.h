#include "Module.h"

class Switcher : public IModule {
private:
	int ternary = false;
	int ternary1 = false;
	bool autos = false;
	bool ss = false;
	bool swap = false;
	bool ownage = false;
	bool ternaryO = false;
	bool toggler = false;

public:
	Switcher();
	~Switcher();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onAttack(C_Entity* attackedEnt) override;
	virtual void onTick(C_GameMode* gm) override;
};
