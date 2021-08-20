
#include "Module.h"
class Emote : public IModule {

public:
	Emote();
	~Emote();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
