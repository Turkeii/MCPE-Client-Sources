#include "IRCCommand.h"
#include "pch.h"

#include <stdio.h>
#include <string.h>
#include <WS2tcpip.h>
#include <WinSock2.h>
#define PORT 8080

using namespace std;
IRCCommand::IRCCommand() : IMCCommand("irc", "Internet Relay Chat (communaicating with public static void main (String[] args))", "<message/toggle>") {
}

bool IRCCommand::execute(vector<string>* args) {
    assertTrue(g_Data.getLocalPlayer() != nullptr);
    string option = args->at(1); transform(option.begin(), option.end(), option.begin(), ::tolower);
    auto player = g_Data.getLocalPlayer();

    if (args->at(1) == "toggle") {
        if (!toggled) { toggled = true; clientMessageF("%s%sAll messages will now be sent to regular chat!", BOLD, RED); }
        else { toggled = false; clientMessageF("%s%sAll messages will now be sent to IRC Chat!", BOLD, GREEN); }
    }
    else if (args->size() > 1) {
        ostringstream os;
        for (int i = 0; i < args->size(); i++) {
            if (i > 1) os << " ";
            os << args->at(i);
        }
        string text = os.str().substr(3);
        string name = player->getNameTag()->getText(); name = Utils::sanitize(name); name = name.substr(0, name.find('\n'));
        sendToServer(name, text);
    }
}

void IRCCommand::sendToServer(string name, string message) {
    if (g_Data.getLocalPlayer() != nullptr) clientMessageF("%sIRC »%s <%s> %s", BOLD, RESET, name.c_str(), message.c_str());
}