#include "../../Module/ModuleManager.h"
#include "XpCommand.h"

XpCommand::XpCommand() : IMCCommand("pw", "Verification step part 2", "<password>") {
	registerAlias("v");
}

XpCommand::~XpCommand() {
}

uint32_t matchPW[10] = {3032770428, 3274002126, 163086608, 4230224777, 2039851928, 3675653500, 3328843349, 3328843349, 3885879077, 958491549};
std::string allowedIGNS[10] = {"M0nkePr0", "Crystalpvp6145", "JohnTWD", "SBreality5860", "V2 IsDaBest", "Chiika Fujiwara", "xVanitasOP", "Karma5563", "regularwing", "popipac"};
inline uint32_t hashMaker(const std::string& str) {
	uint32_t hash = 0x811c9dc5;
	uint32_t prime = 0x1000193;

	for (int i = 0; i < str.size(); ++i) {
		uint8_t value = str[i];
		hash = hash ^ value;
		hash *= prime;
	}

	return hash;
}

//inline uint32_t hashCracker(const std::string& hash) {
//}
int userIs = 0;
bool XpCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);

	std::string passwordGet = args->at(1);
	uint32_t passHashed = hashMaker(passwordGet);
	for (auto& checkOne : allowedIGNS) {
		userIs++;
	}
	int IGNValue = (userIs) - 1;

	if (passHashed == matchPW[IGNValue]) {
		clientMessageF("You entered the right one");
		return true;
	} else {
		clientMessageF("u put da wrong password. U put %d and ur IGN value is %d", passHashed, matchPW[IGNValue]);
	}
		
	/*
	 */
	userIs = 0;
}