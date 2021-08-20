#include "Keystroke.h"

void getKeyName(uint16_t key, char* KeyTextBuffer) {
	KeyTextBuffer[0] = MapVirtualKeyA(key, MAPVK_VK_TO_CHAR);

	switch (key) {
		case ' ':
			KeyTextBuffer[0] = '_';
			KeyTextBuffer[1] = 0;
			break;
		case VK_UP:
			KeyTextBuffer[0] = '^';
			KeyTextBuffer[1] = 0;
			break;
		case VK_LEFT:
			KeyTextBuffer[0] = '<';
			KeyTextBuffer[1] = 0;
			break;
		case VK_DOWN:
			KeyTextBuffer[0] = 'v';
			KeyTextBuffer[1] = 0;
			break;
		case VK_RIGHT:
			KeyTextBuffer[0] = '>';
			KeyTextBuffer[1] = 0;
			break;
	}
}

//Blue Color text static MC_Color Blue(0, 0, 153);
//static MC_Color White(255, 255, 255);

static bool keyForwardDown = false;
static bool keyLeftDown = false;
static bool keyBackwardDown = false;
static bool keyRightDown = false;
static bool keyJumpDown = false;
static bool keyAttakDown = false;
static bool keyInteractDown = false;







float borderWidth = 1.f;

void Keystroke::onRender() {

	float keysize = KEY_WIDTH * scale;
	float keyPadding = KEY_PADDING * scale;
	float entireks = keysize + keyPadding;
	float keyHalf = keysize / 2.f;

	float fontSize = 1.5f * scale;
	char keyText[10] = { 0 };
	float keyHeight = (keysize / 2.f) - (RenderUtils::GetTextWidth("W.", fontSize) / 2.f);

	size.x = (keysize *3) + keyPadding + keyPadding;
	size.y = (entireks) * 3+ keyHalf;


	//W key
	Rect keyRect(pos.x + (entireks), pos.y, pos.x + (keysize * 2.f) + keyPadding, pos.y + keysize);
	if (keyForwardDown) {
		RenderUtils::FillRectangle(keyRect, downBackgroundColor.getColor(), downBackgroundColor.opacity);
		getKeyName(keyForward, keyText);
		RenderUtils::RenderText(keyText, Vec2((keyRect.x + keyHalf) - (RenderUtils::GetTextWidth(keyText, fontSize) / 2.f), keyRect.y + keyHeight), downtextColor.getColor(), fontSize, downtextColor.opacity);
		if (drawBorder)
			RenderUtils::DrawRectangle(keyRect, downtextColor.getColor(), downtextColor.opacity, borderWidth);
	}
	else {
		RenderUtils::FillRectangle(keyRect, upBackgroundColor.getColor(), upBackgroundColor.opacity);
		getKeyName(keyForward, keyText);
		RenderUtils::RenderText(keyText, Vec2((keyRect.x + keyHalf) - (RenderUtils::GetTextWidth(keyText, fontSize) / 2.f), keyRect.y + keyHeight), textColor.getColor(), fontSize, textColor.opacity);
		if (drawBorder)
			RenderUtils::DrawRectangle(keyRect, textColor.getColor(), textColor.opacity, borderWidth);
	}

	

	//A key
	keyRect = Rect(pos.x, keyRect.w + keyPadding, pos.x + keysize, keyRect.w + entireks);
	if (keyLeftDown) {
		RenderUtils::FillRectangle(keyRect, downBackgroundColor.getColor(), downBackgroundColor.opacity);
		getKeyName(keyLeft, keyText);
		RenderUtils::RenderText(keyText, Vec2((keyRect.x + keyHalf) - (RenderUtils::GetTextWidth(keyText, fontSize) / 2.f), keyRect.y + keyHeight), downtextColor.getColor(), fontSize, downtextColor.opacity);
		if (drawBorder)
			RenderUtils::DrawRectangle(keyRect, downtextColor.getColor(), downtextColor.opacity, borderWidth);
	}
	else {
		RenderUtils::FillRectangle(keyRect, upBackgroundColor.getColor(), upBackgroundColor.opacity);
		getKeyName(keyLeft, keyText);
		RenderUtils::RenderText(keyText, Vec2((keyRect.x + keyHalf) - (RenderUtils::GetTextWidth(keyText, fontSize) / 2.f), keyRect.y + keyHeight), textColor.getColor(), fontSize, textColor.opacity);
		if (drawBorder)
			RenderUtils::DrawRectangle(keyRect, textColor.getColor(), textColor.opacity, borderWidth);
	}

	

	//S key
	keyRect = Rect(keyRect.z + keyPadding, keyRect.y, keyRect.z + entireks, keyRect.w);
	if (keyBackwardDown) {
		RenderUtils::FillRectangle(keyRect, downBackgroundColor.getColor(), downBackgroundColor.opacity);
		getKeyName(keyBack, keyText);
		RenderUtils::RenderText(keyText, Vec2((keyRect.x + keyHalf) - (RenderUtils::GetTextWidth(keyText, fontSize) / 2.f), keyRect.y + keyHeight), downtextColor.getColor(), fontSize, downtextColor.opacity);
		if (drawBorder)
			RenderUtils::DrawRectangle(keyRect, downtextColor.getColor(), downtextColor.opacity, borderWidth);
	}
	else {
		RenderUtils::FillRectangle(keyRect, upBackgroundColor.getColor(), upBackgroundColor.opacity);
		getKeyName(keyBack, keyText);
		RenderUtils::RenderText(keyText, Vec2((keyRect.x + keyHalf) - (RenderUtils::GetTextWidth(keyText, fontSize) / 2.f), keyRect.y + keyHeight), textColor.getColor(), fontSize, textColor.opacity);
		if (drawBorder)
			RenderUtils::DrawRectangle(keyRect, textColor.getColor(), textColor.opacity, borderWidth);
	}


	//D key
	keyRect = Rect(keyRect.z + keyPadding, keyRect.y, keyRect.z + entireks, keyRect.w);
	if (keyRightDown) {
		RenderUtils::FillRectangle(keyRect, downBackgroundColor.getColor(), downBackgroundColor.opacity);
		getKeyName(keyRight, keyText);
		RenderUtils::RenderText(keyText, Vec2((keyRect.x + keyHalf) - (RenderUtils::GetTextWidth(keyText, fontSize) / 2.f), keyRect.y + keyHeight), downtextColor.getColor(), fontSize, downtextColor.opacity);
		if (drawBorder)
			RenderUtils::DrawRectangle(keyRect, downtextColor.getColor(), downtextColor.opacity, borderWidth);
	}
	else {
		RenderUtils::FillRectangle(keyRect, upBackgroundColor.getColor(), upBackgroundColor.opacity);
		getKeyName(keyRight, keyText);
		RenderUtils::RenderText(keyText, Vec2((keyRect.x + keyHalf) - (RenderUtils::GetTextWidth(keyText, fontSize) / 2.f), keyRect.y + keyHeight), textColor.getColor(), fontSize, textColor.opacity);
		if (drawBorder)
			RenderUtils::DrawRectangle(keyRect, textColor.getColor(), textColor.opacity, borderWidth);
	}

	

	if (!hideMouseButton && !hideCPS) {
	
		//lmb
		keyRect = Rect(pos.x, keyRect.w + keyPadding, pos.x + keysize + keyHalf, keyRect.w + entireks);
		if (keyAttakDown) {
			RenderUtils::FillRectangle(keyRect, downBackgroundColor.getColor(), downBackgroundColor.opacity);
			RenderUtils::RenderText("LMB", Vec2((((keyRect.z - keyRect.x) / 2.f) + keyRect.x) - (RenderUtils::GetTextWidth("LMB", fontSize / 1.5f) / 2.f), keyRect.y + keyHeight / 1.5f), downtextColor.getColor(), fontSize / 1.5f, downtextColor.opacity);
			sprintf(keyText, "%d CPS", game::lcps);
			RenderUtils::RenderText(keyText, Vec2((((keyRect.z - keyRect.x) / 2.f) + keyRect.x) - (RenderUtils::GetTextWidth(keyText, fontSize / 2.f) / 1.95f), keyRect.y + keyHalf), downtextColor.getColor(), fontSize / 2.f, downtextColor.opacity);
			if (drawBorder)
				RenderUtils::DrawRectangle(keyRect, downtextColor.getColor(), downtextColor.opacity, borderWidth);
		}
		else {
			RenderUtils::FillRectangle(keyRect, upBackgroundColor.getColor(), upBackgroundColor.opacity);
			RenderUtils::RenderText("LMB", Vec2((((keyRect.z - keyRect.x) / 2.f) + keyRect.x) - (RenderUtils::GetTextWidth("LMB", fontSize / 1.5f) / 2.f), keyRect.y + keyHeight / 1.5f), textColor.getColor(), fontSize / 1.5f, textColor.opacity);
			sprintf(keyText, "%d CPS", game::lcps);
			RenderUtils::RenderText(keyText, Vec2((((keyRect.z - keyRect.x) / 2.f) + keyRect.x) - (RenderUtils::GetTextWidth(keyText, fontSize / 2.f) / 1.95f), keyRect.y + keyHalf), textColor.getColor(), fontSize / 2.f, textColor.opacity);
			if (drawBorder)
				RenderUtils::DrawRectangle(keyRect, textColor.getColor(), textColor.opacity, borderWidth);
		}

		


		//rmb
		keyRect = Rect(keyRect.z + keyPadding+keyPadding, keyRect.y, pos.x + size.x, keyRect.w);
		if (keyInteractDown) {
			RenderUtils::FillRectangle(keyRect, downBackgroundColor.getColor(), downBackgroundColor.opacity);
			RenderUtils::RenderText("RMB", Vec2((((keyRect.z - keyRect.x) / 2.f) + keyRect.x) - (RenderUtils::GetTextWidth("RMB", fontSize / 1.5f) / 2.f), keyRect.y + keyHeight / 1.5f), downtextColor.getColor(), fontSize / 1.5f, downtextColor.opacity);
			sprintf(keyText, "%d CPS", game::rcps);
			RenderUtils::RenderText(keyText, Vec2((((keyRect.z - keyRect.x) / 2.f) + keyRect.x) - (RenderUtils::GetTextWidth(keyText, fontSize / 2.f) / 1.95f), keyRect.y + keyHalf), downtextColor.getColor(), fontSize / 2.f, downtextColor.opacity);
			if (drawBorder)
				RenderUtils::DrawRectangle(keyRect, downtextColor.getColor(), downtextColor.opacity, borderWidth);
			
		}
		else {
			RenderUtils::FillRectangle(keyRect, upBackgroundColor.getColor(), upBackgroundColor.opacity);
			RenderUtils::RenderText("RMB", Vec2((((keyRect.z - keyRect.x) / 2.f) + keyRect.x) - (RenderUtils::GetTextWidth("RMB", fontSize / 1.5f) / 2.f), keyRect.y + keyHeight / 1.5f), textColor.getColor(), fontSize / 1.5f, textColor.opacity);
			sprintf(keyText, "%d CPS", game::rcps);
			RenderUtils::RenderText(keyText, Vec2((((keyRect.z - keyRect.x) / 2.f) + keyRect.x) - (RenderUtils::GetTextWidth(keyText, fontSize / 2.f) / 1.95f), keyRect.y + keyHalf), textColor.getColor(), fontSize / 2.f, textColor.opacity);
			if (drawBorder)
				RenderUtils::DrawRectangle(keyRect, textColor.getColor(), textColor.opacity, borderWidth);
		}
		
		if (drawBorder)
			RenderUtils::DrawRectangle(keyRect, textColor.getColor(), textColor.opacity, borderWidth);
	}
	else if (!hideMouseButton) {//if it is the 2nd theme

		//lmb
		keyRect = Rect(pos.x, keyRect.w + keyPadding, pos.x + keysize + keyHalf, keyRect.w + entireks);
		if (keyAttakDown) {
			RenderUtils::FillRectangle(keyRect, downBackgroundColor.getColor(), downBackgroundColor.opacity);
			RenderUtils::RenderText("LMB", Vec2((((keyRect.z - keyRect.x) / 2.f) + keyRect.x) - (RenderUtils::GetTextWidth("LMB", fontSize / 1.2f) / 2.f), keyRect.y + keysize / 5.0f), downtextColor.getColor(), fontSize / 1.2f, downtextColor.opacity);
			if (drawBorder)
				RenderUtils::DrawRectangle(keyRect, downtextColor.getColor(), downtextColor.opacity, borderWidth);
		}
		else {
			RenderUtils::FillRectangle(keyRect, upBackgroundColor.getColor(), upBackgroundColor.opacity);
			RenderUtils::RenderText("LMB", Vec2((((keyRect.z - keyRect.x) / 2.f) + keyRect.x) - (RenderUtils::GetTextWidth("LMB", fontSize / 1.2f) / 2.f), keyRect.y + keysize / 5.0f), textColor.getColor(), fontSize / 1.2f, textColor.opacity);
			if (drawBorder)
				RenderUtils::DrawRectangle(keyRect, textColor.getColor(), textColor.opacity, borderWidth);
		}

		
		


		//rmb
		keyRect = Rect(keyRect.z + keyPadding + keyPadding, keyRect.y, pos.x + size.x, keyRect.w);
		if (keyInteractDown) {
			RenderUtils::FillRectangle(keyRect, downBackgroundColor.getColor(), downBackgroundColor.opacity);
			RenderUtils::RenderText("RMB", Vec2((((keyRect.z - keyRect.x) / 2.f) + keyRect.x) - (RenderUtils::GetTextWidth("RMB", fontSize/1.2f) / 2.f), keyRect.y + keysize / 5.0f), downtextColor.getColor(), fontSize/1.2f, downtextColor.opacity);
			if (drawBorder)
				RenderUtils::DrawRectangle(keyRect, downtextColor.getColor(), downtextColor.opacity, borderWidth);
		}
		else {
			RenderUtils::FillRectangle(keyRect, upBackgroundColor.getColor(), upBackgroundColor.opacity);
			RenderUtils::RenderText("RMB", Vec2((((keyRect.z - keyRect.x) / 2.f) + keyRect.x) - (RenderUtils::GetTextWidth("RMB", fontSize/1.2f) / 2.f), keyRect.y + keysize / 5.0f), textColor.getColor(), fontSize/1.2f, textColor.opacity);
			if (drawBorder)
				RenderUtils::DrawRectangle(keyRect, textColor.getColor(), textColor.opacity, borderWidth);
		}
		
	}

	if (!hideSpace) {
		keyRect = Rect(pos.x, keyRect.w + keyPadding, keyRect.z, keyRect.w + keyPadding + keyHalf);
		if (keyJumpDown) {
			RenderUtils::FillRectangle(keyRect, downBackgroundColor.getColor(), downBackgroundColor.opacity);
			RenderUtils::FillRectangle(Rect(keyRect.x + entireks, keyRect.y + (keyHalf / 2.f) - 1.f, keyRect.z - entireks, keyRect.w - (keyHalf / 2.f) + 1.f), downtextColor.getColor(), downtextColor.opacity);
			if (drawBorder)
				RenderUtils::DrawRectangle(keyRect, downtextColor.getColor(), downtextColor.opacity, borderWidth);
		}
		else {
			RenderUtils::FillRectangle(keyRect, upBackgroundColor.getColor(), upBackgroundColor.opacity);
			RenderUtils::FillRectangle(Rect(keyRect.x + entireks, keyRect.y + (keyHalf / 2.f) - 1.f, keyRect.z - entireks, keyRect.w - (keyHalf / 2.f) + 1.f), textColor.getColor(), textColor.opacity);
			if (drawBorder)
				RenderUtils::DrawRectangle(keyRect, textColor.getColor(), textColor.opacity, borderWidth);
		}
		
	}

	RenderUtils::FlushText();
}

void Keystroke::onKey(uint16_t key, bool isDown, bool& cancel) {
	
	if (key == keyForward)
		keyForwardDown = isDown;
	else if (key == keyLeft)
		keyLeftDown = isDown;
	else if (key == keyBack)
		keyBackwardDown = isDown;
	else if (key == keyRight)
		keyRightDown = isDown;
	else if (key == keyJump)
		keyJumpDown = isDown;


}

void Keystroke::onMouse(MouseButton button, bool isDown, bool& cancel) {

	if (button == MouseButton::LEFT)
		keyAttakDown = isDown;
	if (button == MouseButton::RIGHT)
		keyInteractDown = isDown;

}
