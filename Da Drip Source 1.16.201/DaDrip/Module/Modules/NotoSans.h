#pragma once
#pragma once
#include "../../DrawUtils.h"
#include "Module.h"
class NotoSans : public IModule {

public:
	NotoSans();
	~NotoSans();
	virtual const char* getModuleName() override;
};
