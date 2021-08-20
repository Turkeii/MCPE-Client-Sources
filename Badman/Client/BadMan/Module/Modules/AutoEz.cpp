#include "AutoEz.h"

AutoEz::AutoEz() : IModule(0x0, Category::COMBAT, "Sends a message after you kill someone") {
}

AutoEz::~AutoEz() {
}

const char* AutoEz::getModuleName() {
	return ("Killsults");
}

static std::vector<C_Entity*> targetList;
void findEntity995(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (currentEntity->getEntityTypeId() != 63)  // player
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 7) {
		targetList.push_back(currentEntity);
	}
}

void AutoEz::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (counter == 0)
		RandMessage = "plz no repotr i no want ban plesae!";
	else if (counter == 1)
		RandMessage = "your like a lightswitch, even a little kid could turn you on";
	else if (counter == 2)
		RandMessage = "Badman On top";
	else if (counter == 3)
		RandMessage = "welcome to my basement";
	else if (counter == 4)
		RandMessage = "I'd give you a helmet, but nothing that gets through your thick skull will be stopped by metal, and there's nothing to damage anyway.";
	else if (counter == 5)
		RandMessage = "yo whens the documentary crew coming to your house to film the next episode of my 600 pound life?";
	else if (counter == 6)
		RandMessage = "It's pointless to insult you because you'll die before you figure out.";
	else if (counter == 7)
		RandMessage = "your face makes onions cry";
	else if (counter == 8)
		RandMessage = "You're like Rapunzel but the only thing you let down is everyone else.";
	else if (counter == 9)
		RandMessage = "you bring everyone so much joy! you know, when you leave the room. but, still";
	else if (counter == 10)
		RandMessage = "you are missing a brain";
	else if (counter == 11)
		RandMessage = "Your father would've been disappointed in you, had he actually stayed.";
	else if (counter == 12)
		RandMessage = "Want some free skills? check out discord.gg/B6rHK2yXdU";
	else if (counter == 13)
		RandMessage = "you're so ugly your portraits hang themselves";
	else if (counter == 14)
		RandMessage = "Two wrongs don't make a right, just look at your parents.";
	else if (counter == 15)
		RandMessage = "At first I thought you're brave, but then I realized you're just stupid.";
	else if (counter == 16)
		RandMessage = "you do be lookin' kinda bad at the game";
	else if (counter == 17)
		RandMessage = "i speak english not your gibberish";
	else if (counter == 18)
		RandMessage = "I heard when you were a child your mother wanted to hire somebody to take care of you, but the mafia wanted too much.";
	else if (counter == 19)
		RandMessage = "you really like taking L's";
	else if (counter == 20)
		RandMessage = "fuckk you";
	else if (counter == 21)
		RandMessage = "If you really want to know about mistakes, you should ask your parents.";
	else if (counter == 22)
		RandMessage = "you are the type of person to think FOV increases reach";
	else if (counter == 23)
		RandMessage = "i'd insult you after that death but it's funnier to let you imagine what i'm calling you";
	else if (counter == 24)
		RandMessage = "Yo mama so fat wen she jumped in the ocean the whales started singing We Are Family.";
	else if (counter == 25)
		RandMessage = "Stick your hand in my asss and jjerk off with my sshit";
	else if (counter == 26)
		RandMessage = "Do your keepers a huge favor: do a triple summersault through the air, and disappear up your own assshole.";
	else if (counter == 27)
		RandMessage = "i don't cheat, you just need to click faster";
	else if (counter == 28)
		RandMessage = "i bet you probably shop at Costco";
	else if (counter == 29)
		RandMessage = "Are you always an idiot or just when I'm around?";
	else if (counter == 30)
		RandMessage = "here's your tickets to the juice wrld concert";
	else if (counter == 31)
		RandMessage = "Here's 20 cents, call all your friends and give me back the change.";
	else if (counter == 32)
		RandMessage = "You're like my fish tank, you're mostly water, you've got crabs, and you're full of crap.";
	else if (counter == 33)
		RandMessage = "Out of 100,000 sperm, you were the fastest?";
	else if (counter == 34)
		RandMessage = "drown in your own salt";
	else if (counter == 35)
		RandMessage = "even your mom is better than you in this game";
	else if (counter == 36)
		RandMessage = "It looks like your face caught on fire and someone tried to put it out with a fork.";
	else if (counter == 37)
		RandMessage = "report me im really scared";
	else if (counter == 38)
		RandMessage = "You must think your strong, but you only smell strong.";
	else if (counter == 39)
		RandMessage = "you deserved to be bhopped on";
	else if (counter == 40)
		RandMessage = "i'd smack you, but that would be animal abuse";
	else if (counter == 41)
		RandMessage = "respond in 3 seconds or gay";
	else if (counter == 42)
		RandMessage = "ah yes all team on me i dare you";
	else if (counter == 43)
		RandMessage = "pee poo";
	else if (counter == 44)
		RandMessage = "imagine dying LLL";
	else if (counter == 45)
		RandMessage = "if your so mad about how i play the game why don’t you leave :smile:";
	else if (counter == 46)
		RandMessage = "https://discord.gg/E8yUcG7nz6";
	else if (counter == 47)
		RandMessage = "join if gay";
	else if (counter == 48)
		RandMessage = "BTC hype might end by then if we out of lockdown";
	else if (counter == 49)
		RandMessage = "When you rely on a shittyy anti cheat";
	else if (counter == 50)
		RandMessage = "Fuckedd your mom worse than this anti cheat";
	else if (counter == 51)
		RandMessage = "i send alot of packets when i jump";
	else if (counter == 52)
		RandMessage = "Learn your alphabet with the Badman client: OldGreggo, weedelbhoy1, Smoop";
	else if (counter == 53)
		RandMessage = "Download Badman to kick asss while listening to some badasss music!";
	else if (counter == 54)
		RandMessage = "Why Badman? Cause it is the addition of pure skill and incredible intellectual abilities";
	else if (counter == 55)
		RandMessage = "Badman users belike: Hit or miss I guess I never miss!";
	else if (counter == 56)
		RandMessage = "You have been oofed by Badman oof oof";
	else if (counter == 57)
		RandMessage = "You have been oofed by Badman oof oof";
	else if (counter == 58)
		RandMessage = "i think rex airbender was an alt of penguin";
	else if (counter == 59)
		RandMessage = "Wow! My combo is Badman'n!";
	else if (counter == 60)
		RandMessage = "What should I choose? Badman or Badman?";
	else if (counter == 61)
		RandMessage = "Bigmama and Badmama";
	else if (counter == 62)
		RandMessage = "I don't hack I just Badman";
	else if (counter == 63)
		RandMessage = "Badman client is your new home";
	else if (counter == 63)
		RandMessage = "In need of a cute present for Christmas? Badman is all you need!";
	else if (counter == 64)
		RandMessage = "I have a good Badman config, don't blame me";
	else if (counter == 65)
		RandMessage = "Don't piss me off or you will discover the true power of Badman's inf reach";
	else if (counter == 66)
		RandMessage = "Badman never dies";
	else if (counter == 67)
		RandMessage = "Maybe I will be Badman, I am already Badman";
	else if (counter == 68)
		RandMessage = "Badman will help you! Oops, i killed you instead.";
	else if (counter == 69)
		RandMessage = "NoHaxJustBadman";
	else if (counter == 70)
		RandMessage = "Do like Tenebrous, subscribe to OldGreggo!";
	else if (counter == 71)
		RandMessage = "Badman. The only client run by speakers of Breton";
	else if (counter == 72)
		RandMessage = "Order free baguettes with Badman client";
	else if (counter == 73)
		RandMessage = "Another Badman user? Awww man";
	else if (counter == 74)
		RandMessage = "Badman utility client no hax 100%";
	else if (counter == 75)
		RandMessage = "Moyang wants to know Badman owner's location [Accept] [Deny]";
	else if (counter == 76)
		RandMessage = "MICROJANG WILL HELP ME TAKE DOWN A MINECRAFT CLIENT MADE BY PEOPLE THAT PROBABLY AREN'T EVEN 18+";
	else if (counter == 77)
		RandMessage = "Stop it, get some help! Get Badman";
	else if (counter == 78)
		RandMessage = "Badman users belike: Hit or miss I guess I never miss!";
	else if (counter == 79)
		RandMessage = "I dont hack i just have Badman Gaming Chair";
	else if (counter == 80)
		RandMessage = "Stop Hackustation me cuz im just Badman";
	else if (counter == 81)
		RandMessage = "B. A. D. M. A. N. Hack with me today!";
	else if (counter == 82)
		RandMessage = "Imagine using anything but Badman";
	else if (counter == 83)
		RandMessage = "No hax just beta testing the anti-cheat with Badman";
	else if (counter == 84)
		RandMessage = "Don't forget to report me for Badman on the forums!";
	else if (counter == 85)
		RandMessage = "don't use Badman? ok boomer";
	else if (counter == 86)
		RandMessage = "How come a noob like you not use Badman?";
	else if (counter == 87)
		RandMessage = "A mother becomes a true grandmother the day she gets Badman 1.0";
	else if (counter == 88)
		RandMessage = "Fly faster than light, only available in Badman™";
	else if (counter == 89)
		RandMessage = "Behind every Badman user, is an incredibly cool human being. Trust me, cooler than you.";
	else if (counter == 90)
		RandMessage = "Your client sucks, just get Badman";
	else if (counter == 91)
		RandMessage = "Badman made this world a better place, killing you with it even more";
	else if (counter == 92)
		RandMessage = "Stop being a disapointment to your parents and download Badman!";
	else if (counter == 93)
		RandMessage = "you've been killed by a Badman user, rejoice!";
	else if (counter == 94)
		RandMessage = "I'm not hacking it's just my new hair dryer!";
	else if (counter == 95)
		RandMessage = "I'm not hacking it's just my 871619-B21 HP Intel Xeon 8180 2.5GHz DL380 G10 processor!";
	else if (counter == 96)
		RandMessage = "weedelbhoy1 is my dad!";
	else if (counter == 97)
		RandMessage = "Report me for Badman!";
	else if (counter == 98)
		RandMessage = "Once I started using Badman I started getting a lot of matches on tinder!";
	else if (counter == 99)
		RandMessage = "Hive killed by Badman";
	else if (counter == 100)
		RandMessage = "#BadmanOnTop";
	else if (counter == 101)
		RandMessage = "Badman is the best client for any server!";
	else if (counter == 102)
		RandMessage = "Don't be like the guy who just died and download Badman!";
	else if (counter == 103)
		RandMessage = "I'm not hacking you're just bad!";
	else if (counter == 104)
		RandMessage = "Get Badman noob!";
	else if (counter == 105)
		RandMessage = "do you buy your groceries at the dollar store?";
	else if (counter == 106)
		RandMessage = "what do your clothes have in common with your skills? they're both straight out of a dumpster";
	else if (counter == 107)
		RandMessage = "cry all you want, that monkey George Floyd died of a fentanyl overdose";
	else if (counter == 108)
		RandMessage = "i'd tell you to uninstall, but your aim is so bad you'd miss and click on your ccuck pporn instead";
	if (counter == 109)
		RandMessage = "im not saying you're worthless, but i'd unplug ur life support to charge my phone";
	else if (counter == 110)
		RandMessage = "how are you so bad? just practice your aim and hold w";
	else if (counter == 111)
		RandMessage = "you look like you were drawn with my left hand";
	else if (counter == 112)
		RandMessage = "you're so white that you don't play on vanilla, you play on clear";
	else if (counter == 113)
		RandMessage = "your difficulty settings must be stuck on easy";
	else if (counter == 114)
		RandMessage = "go commit stop breathing plz";
	else if (counter == 115)
		RandMessage = "go take a long walk off a short bridge";
	else if (counter == 116)
		RandMessage = "lol you probably speak dog eater";
	else if (counter == 117)
		RandMessage = "your code makes namet look like dort";
	else if (counter == 118)
		RandMessage = "report me im really scared";
	else if (counter == 119)
		RandMessage = "Ladies and Gentleman: The runner-up to the participation award!";
	else if (counter == 120)
		RandMessage = "some kids were dropped at birth, but you got thrown at the wall";
	else if (counter == 121)
		RandMessage = "you're the type of guy to quickdrop irl";
	else if (counter == 122)
		RandMessage = "i bet you thought gcheat was a type of STD";
	else if (counter == 123)
		RandMessage = "you're the type to get 3rd place in a 1v1";
	else if (counter == 124)
		RandMessage = "you have an IQ lower than that of a bathtub";
	else if (counter == 125)
		RandMessage = "your parents abandoned you, then the orphanage did the same";
	else if (counter == 126)
		RandMessage = "you go to the doctors and they say you shrunk";
	else if (counter == 127)
		RandMessage = "Badman, drop kicking lil' kids and fat obese staff since 2021";
	else if (counter == 128)
		RandMessage = "man with chocolate on face gif";
	else if (counter == 129)
		RandMessage = "yo mama so fat, she sat on an iphone and it became an ipad";
	else if (counter == 130)
		RandMessage = "search up blue waffle on google, it's so cute";
	else if (counter == 131)
		RandMessage = "you smell like a moldy ballsackk";
	else if (counter == 132)
		RandMessage = "your grandmother has chlamydiaa";
	else if (counter == 133)
		RandMessage = "welcome to my rrape dungeon! population: you";
	else if (counter == 134)
		RandMessage = "you're so ggay you spent twice as much on a coloured iPhone just to join the 41% a day later";
	else if (counter == 135)
		RandMessage = "your cumulative intelligence is that of a rock";
	else if (counter == 136)
		RandMessage = "man with chocolate on face gif";
	else if (counter == 137)
		RandMessage = "you shouldn't be running away with all these monkeys coming after you";
	else if (counter == 138)
		RandMessage = "ah yes touch me bum like yer dad touchs you";
	else if (counter == 139)
		RandMessage = "i may be hacking but atleast my dads still around";
	else if (counter == 140)
		RandMessage = "how do you keep an idiot amused? watch this message until it fades away";
	else if (counter == 141)
		RandMessage = "Badman, The only client to have a competent dev team";
	else if (counter == 142)
		RandMessage = "Fadeaway moment";
	else if (counter == 143)
		RandMessage = "soy face";
	else if (counter == 144)
		RandMessage = "you should get badman";
	else if (counter == 145)
		RandMessage = "your the reason why birth control was a thing";
	else if (counter == 146)
		RandMessage = "Clown";
	else if (counter == 147)
		RandMessage = "go breath under water";
	else if (counter == 148)
		RandMessage = "go shove a cucumber where the sun dont shine";
	else if (counter == 149)
		RandMessage = "mineplex monkey";
	else if (counter == 150)
		RandMessage = "sister humper";
	else if (counter == 151)
		RandMessage = "Toe Eyed Cabbage";
	else if (counter == 152)
		RandMessage = "zebrafuckerr";
	else if (counter == 153)
		RandMessage = "Badman aint having non of that shhit";
	else if (counter == 154)
		RandMessage = "poop breath";
	else if (counter == 155)
		RandMessage = "Spell my name right, G-R-E, Double-G, O";
	else if (counter == 156)
		RandMessage = "she say daddy i can feel it in my tummy";

	targetList.clear();

	g_Data.forEachEntity(findEntity995);
	if (!targetList.empty() && g_Data.isInGame()) {
		if (GameData::canUseMoveKeys()) {
			if (counter >= 157) {
				counter = 0;
			} else
				counter++;
			if (targetList[0]->isAlive() && targetList[0]->height > 1.5f && targetList[0]->damageTime > 1) {
				foundPlayer = true;
			}

			if (foundPlayer && !targetList[0]->isAlive() && !targetList[0]->canShowNameTag() && targetList[0]->getDeathTime() >= 0 && targetList[0]->getNameTag()->getTextLength() > 1) {
				isDead = true;
			}

			if (isDead) {
				C_TextPacket textPacket;
				textPacket.message.setText(RandMessage);
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
				foundPlayer = false;
				isDead = false;
			}
		}
	}
	if (targetList.empty()) {
		foundPlayer = false;
		isDead = false;
	}
}