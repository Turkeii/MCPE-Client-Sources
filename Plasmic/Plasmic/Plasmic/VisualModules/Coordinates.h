#pragma once

#include "../Module.h"


class Coordinates : public VisualModule {

public:
	bool showXYZ = false;
	bool sameLine = false;
	bool precise = false;
	float scale = 1.f;
	ClickguiColor textColor = ClickguiColor(1.f, 1.f, 1.f, 1.f, true);
	ClickguiColor backgroundColor = ClickguiColor(0.156862f, 0.156862f, 0.156862f, 0.4f, true);


	Coordinates();

	virtual void onEject() override;


	virtual void onRender() override;
	
};

