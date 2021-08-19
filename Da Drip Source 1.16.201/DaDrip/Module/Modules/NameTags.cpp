#include "NameTags.h"

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

bool itemTags = false;

NameTags::NameTags() : IModule(0, Category::VISUAL, "Shows better nametags above players that can be seen from a lot more far aways") {
	this->registerBoolSetting("Display Armor", &this->displayArmor, this->displayArmor);
	this->registerBoolSetting("Item Tags", &itemTags, itemTags);
}

NameTags::~NameTags() {
}

const char* NameTags::getModuleName() {
	return ("NameTags");
}

void drawNameTags(C_Entity* ent, bool isRegularEntitie) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	static auto nameTagsMod = moduleMgr->getModule<NameTags>();

	if (nameTagsMod == nullptr)
		return;

	if (ent != localPlayer) {
		if (ent->getEntityTypeId() == 63 && nameTagsMod != nullptr) {
			if (ent->timeSinceDeath > 0)
				return;

			if (ent->getNameTag()->getTextLength() < 1)
				return;

			nameTagsMod->nameTags.insert(Utils::sanitize(ent->getNameTag()->getText()));
			float dist = ent->getPos()->dist(g_Data.getClientInstance()->levelRenderer->origin);
			DrawUtils::drawNameTags(ent, fmax(0.6f, 3.f / dist), true);
			DrawUtils::flush();
		}

		if (ent->getEntityTypeId() == 64 && itemTags) {
			C_ItemStack* stack = (C_ItemStack*)((uintptr_t)ent + 0x688);

			std::stringstream textbuild;
			if (stack->item != nullptr) {
				if (stack->count > 1)
					textbuild << std::to_string(stack->count) << "x ";
				
				bool wasSpace = true;
				std::string name = stack->getItem()->name.getText();
				for (auto i = 0; i < name.size(); i++) {
					if (wasSpace) {
						name[i] = toupper(name[i]);
						wasSpace = false;
					}
					
					if (name[i] == '_') {
						wasSpace = true;
						name[i] = ' ';
					}
				}

				textbuild << name;
			} else {
				textbuild << "No item";
			}
			std::string text = textbuild.str();
				
			vec2_t textPos = DrawUtils::worldToScreen(*ent->getPos());
			float size = fmax(0.6f, 3.f / g_Data.getClientInstance()->levelRenderer->origin.dist(*ent->getPos()));

			float itemHeight = 15.f * size;
			float textHeight = DrawUtils::getFontHeight(size);
			float itemSize = size;

			if (itemHeight > textHeight) {
				itemSize *= textHeight / itemHeight;
				itemHeight = textHeight;
			}

			float textWidth = DrawUtils::getTextWidth(&text, size) + (15.f * itemSize + 3.f * size);

			textPos.y -= textHeight * 1.5f;
			textPos.x -= textWidth / 2.f;

			vec4_t rectPos;
			rectPos.x = textPos.x - 1.f * size;
			rectPos.y = textPos.y - 1.f * size;
			rectPos.z = textPos.x + textWidth + 1.f * size;
			rectPos.w = textPos.y + textHeight + 2.f * size;

			vec2_t itemPos = textPos;
			textPos.x += 15.f * itemSize + 3.f * size;

			if (!moduleMgr->getModule<NotoSans>()->isEnabled()) {
				textPos.y += 1.f * size;
			}

			DrawUtils::fillRectangle(rectPos, MC_Color(20, 20, 20), 0.8f);
			DrawUtils::drawItem(stack, itemPos, 1.f, itemSize, false);
			DrawUtils::drawText(textPos, &text, MC_Color(255, 255, 255), size);
			DrawUtils::flush();
		}
	}
}

void NameTags::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();

	if (nameTags.size() > 100)
		nameTags.clear();

	if (localPlayer != nullptr && GameData::canUseMoveKeys() && g_Data.getEntityList() != nullptr) {
		std::vector<C_Entity*> temp;
		std::vector<C_Entity*> itemList;

		g_Data.forEachEntity([&](C_Entity* i, bool) {
			if (i->getEntityTypeId() != 64)
				temp.push_back(i);
			else
				itemList.push_back(i);
		});

		vec3_t origin = g_Data.getClientInstance()->levelRenderer->origin;
		std::sort(itemList.begin(), itemList.end(), [origin](const C_Entity* lhs, const C_Entity* rhs) {
			return origin.dist(*lhs->getPos()) < origin.dist(*rhs->getPos());
		});

		std::vector<C_Entity*> swap;
		for (auto i = 0; i < 50; i++) {
			if (i < itemList.size())
				swap.push_back(itemList[i]);
		}

		itemList = swap;
		std::reverse(itemList.begin(), itemList.end());

		temp.insert(temp.end(), itemList.begin(), itemList.end());
		std::sort(temp.begin(), temp.end(), [origin](const C_Entity* lhs, const C_Entity* rhs) {
			return origin.dist(*lhs->getPos()) > origin.dist(*rhs->getPos());
		});
		
		for (C_Entity* ent : temp)
			drawNameTags(ent, true);

	} else {
		nameTags.clear();
	}
}

//rr