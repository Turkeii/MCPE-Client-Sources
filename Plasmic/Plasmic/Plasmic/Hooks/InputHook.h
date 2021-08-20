#pragma once

#include "../Module.h"




class KeyboardHook : public Hook {
public:

	virtual void init() override;

};

class MouseHook : public Hook {
public:

	virtual void init() override;

};