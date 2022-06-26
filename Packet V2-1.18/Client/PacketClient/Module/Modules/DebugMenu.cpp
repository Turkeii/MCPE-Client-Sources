#include "DebugMenu.h"
#include "../ModuleManager.h"

using namespace std;
DebugMenu::DebugMenu() : IModule(VK_F3, Category::UNUSED, "Displays debug information") {
    shouldHide = true;
}

const char* DebugMenu::getRawModuleName() {
    return "DebugMenu";
}

const char* DebugMenu::getModuleName() {
    return "DebugMenu";
}

void DebugMenu::onTick(C_GameMode* gm) {
    shouldHide = true;
}

void DebugMenu::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
    auto player = g_Data.getLocalPlayer();
    if (player == nullptr) return;

    auto interfaceMod = moduleMgr->getModule<Interface>();
    vec3_t* pos = player->getPos();
    string yaw = "Yaw: " + to_string(player->yaw);
    string bodyyaw = "BodyYaw: " + to_string(player->bodyYaw);
    vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSizeReal;
    string width = to_string((int)windowSize.x);
    string height = to_string((int)windowSize.y);
    string stringer = "Display: " + width + "x" + height;
    string multiplayer;
    if (g_Data.getClientInstance()->isInMultiplayerGame()) multiplayer = "Multiplayer";
    else multiplayer = "Singleplayer";
    string pitch = "Pitch: " + to_string(player->pitch);
    string position = "XYZ: " + to_string((int)floorf(pos->x)) + " / " + to_string((int)floorf(pos->y)) + " / " + to_string((int)floorf(pos->z));
    string fps = to_string(g_Data.getFPS()) + " fps";

    string textStr = 
        "Minecraft 1.18.12 (" + (interfaceMod->versionStr + " / PacketClient)\n")
        + multiplayer + "\n"
        + fps + "\n\n"
        + position + "\n\n"
        + yaw + "\n"
        + pitch + "\n"
        + bodyyaw + "\n\n"
        + stringer;
    DrawUtils::drawText(vec2_t(1, 1), &textStr, MC_Color(255, 255, 255), 1, 1, true);
}