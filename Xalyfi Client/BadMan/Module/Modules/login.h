#include "Module.h"

class Verify : public IModule {
public:
	bool passedTest = false;
	std::string authuser[25] = {
		"KaeruKing188",
		"Brown5632",
		"XEzoxX",
		"Brown5632",
		"BossLicense1725",
		"EzBADM4N",
		"ameo1112",
		"MugichaXD",
		"radaokun2989",
		"SyAKq",
		"Sy4Kq",
		"God07213124",
		"ShinX54",
		"rincho3931",
		"Guardian00N",
		"R4NR4NRU",
		"FireXX0001",
		"M0ndqyDX",
		"ShinXeAlt",	
		"SASUGAIJI",
		"Momo554921",
		"victory 2799",
		"Tuesday5197",
		"SBreality5860",
		"shunya 15"};

	bool test = false;

	Verify();
	~Verify();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable();
};
