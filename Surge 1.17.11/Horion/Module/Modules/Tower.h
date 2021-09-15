#pragma once
#include "Module.h"

class Tower : public IModule {
private:
	bool tryTower(vec3_t blockBelow);

public:
	float motion = 0.5f;
	Tower();
	~Tower();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};
