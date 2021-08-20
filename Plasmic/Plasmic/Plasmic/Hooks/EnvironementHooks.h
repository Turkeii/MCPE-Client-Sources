#pragma once
#include "../Module.h"

class TimeOfDayHook : public Hook {
public:
	virtual void init() override;
};


class OverworldGetFogColorHook : public Hook {
public:
	virtual void init() override;
};
class DimensionGetFogColorHook : public Hook {
public:
	virtual void init() override;
};

