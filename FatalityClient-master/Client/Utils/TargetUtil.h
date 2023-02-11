#pragma once
#include "../PacketClient/Module/ModuleManager.h"
#include "../SDK/CEntity.h"
#include <vector>

class TargetUtil {
private:
	static bool containsOnlyASCII(const std::string& string);
public:
	static void init(C_LocalPlayer** lc);
	static bool isValidTarget(C_Entity* ent);
};
