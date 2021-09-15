#pragma once
#include "Module.h"

class Spammer : public IModule {
private:
	bool bypass = true;
	std::string message = "Surge On Top!!!!!!!";

public:
	Spammer();
	~Spammer();

	inline std::string& getMessage() { return message; };
	inline bool& getBypass() { return bypass; };

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};