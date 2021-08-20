
#include "Module.h"
class FastEat : public IModule {
private:
	int dur = 5;

public:
	FastEat();
	~FastEat();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};
