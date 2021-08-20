#include "ServerModule.h"


static char serverText[128] = "server";


void ServerModule::onRender() {
	memset(serverText, 0, 128);

	
	if (game::minecraftGame->networkHandler->raknetInstance->isonaServer())
		if (showPort)
			sprintf_s(serverText, 128, "%s:%d", game::minecraftGame->networkHandler->raknetInstance->serverTextIP.getText(), game::minecraftGame->networkHandler->raknetInstance->serverPort);
		else
			sprintf_s(serverText, 128, "%s", game::minecraftGame->networkHandler->raknetInstance->serverTextIP.getText());
	else
		sprintf(serverText, mltext("Not on a server.", "Pas sur un serveur."));

	size.x = RenderUtils::GetTextWidth(serverText, 1.f * scale);
	size.y = RenderUtils::GetTextWidth("W", 1.0f * scale);
	size.x += 6.f;
	size.y += 6.f;

	RenderUtils::FillRectangle(Rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y), backgroundColor.getColor(), backgroundColor.opacity);

	RenderUtils::RenderText(serverText, Vec2(pos.x + 3.f, pos.y + size.y / 12.f), textColor.getColor(), 1.f * scale, textColor.opacity);
	RenderUtils::FlushText();
}


