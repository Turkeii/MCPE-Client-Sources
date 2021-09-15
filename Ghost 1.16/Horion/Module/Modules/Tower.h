#pragma once
#include "Module.h"

class Tower : public IModule {
private:
	bool rot = true;
	bool tryTower(vec3_t blockBelow);

public:
	Tower();
	~Tower();
	float motion = 0.5f;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};
