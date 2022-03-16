#pragma once
#include "Module.h"
#include "../../DrawUtils.h"
class InstaBreak : public IModule {
public:
       	bool instant = false;
		bool packet = true;
	    bool silent = false;
		bool pre = false;
		int slot = 0;
		int old;
		SettingEnum mode;
		static int constexpr m_instant = 0;
		static int constexpr m_silent = 1;
		static int constexpr m_packet = 2;  // 2b2e
	InstaBreak();
	~InstaBreak();
	// Inherited via IModule
	bool getPick();
	virtual const char* getModuleName() override;
	virtual void onLevelRender() override;
};
