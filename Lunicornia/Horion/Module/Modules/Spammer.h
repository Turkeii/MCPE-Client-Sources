#pragma once
#include "Module.h"

class Spammer : public IModule
{
public:
	int Odelay = 0;
	bool bypass = true;
	int delay = 2;
	std::string message = "f";

	Spammer();
	~Spammer();

	inline std::string& getMessage() { return message; };
	inline int& getDelay() { return delay; };
	inline bool& getBypass() { return bypass; };

	

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};