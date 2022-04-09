
#include "Module.h"
class BlockESP : public IModule {
public:
	bool spawner = false;
	bool dOre = false;
	bool eOre = false;
	bool rOre = false;
	bool gOre = false;
	bool iOre = false;
	bool cOre = false;
	float width = 0.5;
	int range = 5;

	BlockESP();
	~BlockESP();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};