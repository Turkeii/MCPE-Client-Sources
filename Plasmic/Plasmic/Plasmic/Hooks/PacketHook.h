#pragma once
#include "../Module.h"

class SendToServerHook : public Hook {
public:
	virtual void init() override;

};

class OnTextPacketHook : public Hook {
public:
	virtual void init() override;

};

