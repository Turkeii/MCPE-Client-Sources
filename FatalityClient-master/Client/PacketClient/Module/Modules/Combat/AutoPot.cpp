#include "../../../../Utils/TimerUtil.h"
#include "AutoPot.h"

using namespace std;
AutoPot::AutoPot() : IModule(0, Category::COMBAT, "Throws potions for you") {
    registerIntSetting("Health", &health, health, 1, 19);
    registerIntSetting("Delay", &delay, delay, 0, 20);
}

const char* AutoPot::getRawModuleName() {
    return "AutoPot";
}

const char* AutoPot::getModuleName() {
    name = string("AutoPot");
    return name.c_str();
}

void AutoPot::onTick(C_GameMode* gm) {
    auto player = g_Data.getLocalPlayer();
    auto timerUtil = new TimerUtil();
    if (player == nullptr) return;

    shouldThrow = false;
    if (g_Data.canUseMoveKeys()) {
        int playerHealth = player->getHealth();
        auto inv = player->getSupplies()->inventory;

        if (playerHealth < health) {
            for (int i = 0; i < 9; i++) {
                C_ItemStack* stack = inv->getItemStack(i);
                if (stack->item != nullptr) {
                    if (stack->getItem()->itemId == 561) shouldThrow = true;

                    if (shouldThrow) {
                        g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = i;
                        g_Data.getCGameMode()->useItem(*stack);
                        return;

                    }
                }
            }
        }
    }
}

void AutoPot::onPlayerTick(C_Player* plr) {
    if (plr == nullptr) return;

    if (g_Data.canUseMoveKeys() && shouldThrow) {
        plr->pitch = 80;
    }
}

void AutoPot::onSendPacket(C_Packet* packet) {
    auto player = g_Data.getLocalPlayer();
    if (player == nullptr) return;

    if (g_Data.canUseMoveKeys() && shouldThrow) {
        if (packet->isInstanceOf<C_MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>()) {
            auto* inputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
            auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);

            inputPacket->pitch = 80;
            movePacket->pitch = 80;
        }
    }
}