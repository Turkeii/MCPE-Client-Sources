#include "FastUse.h"

using namespace std;
FastUse::FastUse() : IModule(0, Category::EXPLOIT, "Description") {
}

const char* FastUse::getModuleName() {
    return "FastUse";
}

vector<string> allowedItems = {
    "snowball",
    "bottle",
    "splash",
    "rod",
    "bow"
};

void FastUse::onTick(C_GameMode* gm) {
    auto player = g_Data.getLocalPlayer();
    if (player == nullptr || gm == nullptr) return;

    if (g_Data.canUseMoveKeys() && g_Data.isRightClickDown()) {
        C_ItemStack* stack = player->getSupplies()->inventory->getItemStack(player->getSupplies()->selectedHotbarSlot);
        if (stack->item != nullptr && (* stack->item)->itemId != 0) {

            string itemName = stack->getItem()->name.getText();
            for (auto item : allowedItems) {
                if (itemName.find(item) != string::npos) {
                    gm->useItem(*stack);
                }
            }
        }
    }
}