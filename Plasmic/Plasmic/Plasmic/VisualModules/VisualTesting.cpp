#include "VisualTesting.h"

VisualTesting::VisualTesting() : VisualModule("Test Visual", Vec2(50,50), Vec2(100,100), mltext("You can test visual module stuff with this.", "Vous pouvez tester des trucs de module visuel avec cela.")) {
	this->Enable();
}



void VisualTesting::onRender() {

	RenderUtils::FillRectangle(Rect(15, 15, 100, 100), MC_Color(1.f, 1.f, 1.f), 0.5f);
	RenderUtils::RenderText("This is massive gaming", Vec2(100, 100), MC_Color(1.f, 1.f, 1.f), 1.f, 1.f);

}
