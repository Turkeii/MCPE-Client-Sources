#include "../SDK/game.h"

#define sendWorldEditError(...) {game::sendClientChat(__VA_ARGS__); return;}

#define StartCommands sendCommand("/gamerule sendcommandfeedback false")
#define EndCommands sendCommand("/gamerule sendcommandfeedback true")


extern bool cmpAfterFirstSpace(const char* text, const char* compareTo);
extern bool cmpAfterFirstOrSecondSpace(const char* text, const char* compareTo);

extern bool endWith(const char* text, size_t textLenght, const char* compareTo, size_t compareToLenght);
extern bool startWith(const char* text, size_t textLenght, const char* compareTo, size_t compareToLenght);


BlockPos pos1;
BlockPos pos2;


void fixOrder() {
	BlockPos temp;
	if (pos1.x > pos2.x) {
		temp.x = pos1.x;
		pos1.x = pos2.x;
		pos2.x = temp.x;
	}
	if (pos1.y > pos2.y) {
		temp.y = pos1.y;
		pos1.y = pos2.y;
		pos2.y = temp.y;
	}
	if (pos1.z > pos2.z) {
		temp.z = pos1.z;
		pos1.z = pos2.z;
		pos2.z = temp.z;
	}
}
//it must be small in pos1 and big in pos2 you can call fixOrder to make that happen
int getAffectedBlocks() {
	BlockPos t;
	t.x = pos2.x - pos1.x;
	t.y = pos2.y - pos1.y;
	t.z = pos2.z - pos1.z;

	if (t.x == 0)
		t.x = 1;
	if (t.y == 0)
		t.y = 1;
	if (t.z == 0)
		t.z = 1;

	return t.x * t.y * t.z;
}




void updateSelection(BlockPos* pos, bool isPos1) {
	if (isPos1)
		pos1 = *pos;
	else
		pos2 = *pos;
}

CommandRequestPacket* packet = nullptr;


void sendCommand(const char* command) {
	packet->command.setText(command, true);
	game::sendPacket(packet);
}
void sendCommandf(const char* format, ...) {
	static char cmdText[300];
	va_list args;
	va_start(args, format);
	vsprintf(cmdText, format, args);

	packet->command.setText(cmdText, true);
	game::sendPacket(packet);
	//game::sendClientChat(cmdText);
}


void doWorldedit(const char* command, CommandRequestPacket* ipk) {
	packet = ipk;

	if (!strcmp(command, "cut")) {
		fixOrder();

		for (int y = pos1.y; y <= pos2.y; y++) 
			for (int x = pos1.x; x <= pos2.x; x++) 
				sendCommandf("/fill %d %d %d %d %d %d air", x, y, pos1.z, x, y, pos2.z);
		game::sendClientChat("§§d%d blocks where cut", getAffectedBlocks());
	}

	if (startWith(command, 8, "set", 2)) {
		fixOrder();
		const char* args = command + 3;
		if (args[0] == ' ')
			args = args + 1;
		if (args[0] == 0)
			sendWorldEditError("§§cYou need to specify a block to set!\n§§a//set §§dBlockName§§a:§§bBlockData")

		char material[60];
		size_t argl = strlen(args);
		for (int i = 0; i < argl; i++) 
			if (args[i] == ':')
				material[i] = ' ';
			else
				material[i] = args[i];

		StartCommands;
		for (int y = pos1.y; y <= pos2.y; y++)
			for (int x = pos1.x; x <= pos2.x; x++)
				sendCommandf("/fill %d %d %d %d %d %d %s", x, y, pos1.z, x, y, pos2.z, material);
		EndCommands;
		game::sendClientChat("§§d%d %s blocks where set", getAffectedBlocks(), args);
	}


}