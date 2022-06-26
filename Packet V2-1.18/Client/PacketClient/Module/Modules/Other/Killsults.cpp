#include "Killsults.h"

using namespace std;
Killsults::Killsults() : IModule(0, Category::OTHER, "Insults people you kill lol") {
    registerEnumSetting("Mode", &mode, 0);
    mode.addEntry("Normal", 0);
    mode.addEntry("Sigma", 1);
    //mode.addEntry("Custom", 2);
}

const char* Killsults::getRawModuleName() {
    return "Killsults";
}

const char* Killsults::getModuleName() {
    if (mode.getSelectedValue() == 0) name = string("Killsults ") + string(GRAY) + string("Normal");
    if (mode.getSelectedValue() == 1) name = string("Killsults ") + string(GRAY) + string("Custom");
    return name.c_str();
}

string normalMessages[36] = {
    "Download Packet today to kick azs while aiding to some abstractional!",
    "I found you in task manager and I ended your process",
    "What's yellow and can't swim? A bus full of children",
    "You are more disappointing than an unsalted pretzel",
    "Take a shower, you smell like your grandpa's toes",
    "You are not Parghet Clent approved :rage:",
    "I'm not flying, I'm just defying gravity!",
    "Stop running, you weren't going to win",
    "Knock knock, who's there? Your life",
    "Your client has stopped working",
    "Warning, I have detected haram",
    "I don't hack, I just parchet",
    "You should end svchost.exe!",
    "just aided my pantiez",
    "You were an accident",
    "Abstractional Aidz",
    "JACKALOPE TURD BOX",
    "Get dogwatered on",
    "Get 360 No-Scoped",
    "You afraid of me?",
    "Go do the dishes",
    "Job Immediately",
    "Delete System32",
    "I Alt-F4'ed you",
    "Touch grass",
    "jajajaja",
    "Minority",
    "kkkkkk",
    "clean",
    "idot",
    "F"
};

string cheaterMessages[9] = {
    "How does this bypass ?!?!?",
    "Switch to PacketV2 today!",
    "Violently bhopping I see!",
    "Why Zephyr when Packet?",
    "You probably use Zephyr",
    "Must be using Kek.Club+",
    "SelfHarm Immediately.",
    "Man you're violent",
    "Horion moment"
};

string sigmaMessages[2] = {
    "Eat My",
    "Funny Funny Abstractional"
};

void Killsults::onEnable() {
    killed = false;
}

void Killsults::onPlayerTick(C_Player* plr) {
    auto player = g_Data.getLocalPlayer();
    if (player == nullptr) return;

    int random = 0;
    srand(time(NULL));
    if (killed) {
        C_TextPacket textPacket;
        switch (mode.getSelectedValue()) {
        case 0: // Normal
            random = rand() % 36;
            textPacket.message.setText(normalMessages[random]);
            break;
        case 1: // Sigma
            random = rand() % 2;
            textPacket.message.setText(sigmaMessages[random]);
            break;
        }
        textPacket.sourceName.setText(player->getNameTag()->getText());
        textPacket.xboxUserId = to_string(player->getUserId());
        g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
        killed = false;
    }
}