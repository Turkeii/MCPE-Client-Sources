#include "AutoGG.h"

using namespace std;
AutoGG::AutoGG() : IModule(0, Category::OTHER, "Automatically says GG on game end") {
    registerEnumSetting("Server", &server, 0);
    server.addEntry("Hive", 0);
}

const char* AutoGG::getRawModuleName() {
    return "AutoGG";
}

const char* AutoGG::getModuleName() {
    if (server.getSelectedValue() == 0) name = string("AutoGG ") + string(GRAY) + string("Hive");
    return name.c_str();
}

void AutoGG::onEnable() {
    send = false;
}

void AutoGG::onTick(C_GameMode* gm) {
    auto player = g_Data.getLocalPlayer();
    if (player == nullptr) return;

    if (send) {
        C_TextPacket textPacket;
        textPacket.message.setText("GG");
        textPacket.sourceName.setText(player->getNameTag()->getText());
        textPacket.xboxUserId = to_string(player->getUserId());
        g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
        send = false;
    }
}