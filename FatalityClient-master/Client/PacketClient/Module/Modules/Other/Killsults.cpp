#include "Killsults.h"

using namespace std;
Killsults::Killsults() : IModule(0, Category::OTHER, "Insults people you kill lol") {
    registerEnumSetting("Mode", &mode, 0);
    mode.addEntry("Exhibition", 0);
    mode.addEntry("Sigma", 1);
    //mode.addEntry("Custom", 2);
}

const char* Killsults::getRawModuleName() {
    return "Killsult";
}

const char* Killsults::getModuleName() {
    if (mode.getSelectedValue() == 0) name = string("Killsult");
    if (mode.getSelectedValue() == 1) name = string("Killsult");
    return name.c_str();
}

string normalMessages[36] = {
    "oof",
    "i'm surprised that you were able to hit the 'Install' button",
    "2 plus 2 is 4, minus 1 that's your IQ",
    "you probably watch tenebrous videos and are intruiged",
    "That's a #VictoryRoyale!, better luck next time!",
    "are you even trying?",
    "oof",
    "please stop",
    "Don't forget to report me",
    "please stop",
    "IM ON ONIX CLIENT",
    "That's a #VictoryRoyale!, better luck next time!",
    "if the body is 70 percent water how is yours 100 percent salt???",
    "I just Sneezed On Your Forehead",
    "please stop",
    "I's say uninstall but you'd probably miss that too.",
    "Thanks for the free kill!",
    "LMAO you are a Horionuser",
    "IM ON ONIX CLIENT",
    "Don't forget to report me",
    "would you like to hear a joke? Yeah, you ain't getting any",
    "You died in a fricking block game",
    "You just got oneTapped LUL",
    "You got OOFed",
    "Wow, you just died in a block game",
    "You used Horion then got backhanded by the face of the hive",
    "Your dad is bald",
    "Hive thought they could stop us from cheating, huh, you are just as foolish as him",
};

string cheaterMessages[9] = {
    "How does this bypass ?!?!?",
    "Switch to Fatality today!",
    "Violently bhopping I see!",
    "Why Zephyr when Fatality?",
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