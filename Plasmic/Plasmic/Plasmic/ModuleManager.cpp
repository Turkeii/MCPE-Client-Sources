#include "Manager.h"
#include <filesystem>


std::vector<Module*> ModuleManager::moduleList;
std::vector<VisualModule*> ModuleManager::visualModuleList;


//normal modules
#include "Modules/TestModule.h"
#include "Modules/ZoomModule.h"
#include "Modules/Fullbright.h"
#include "Modules/FreeLook.h"
#include "Modules/EnvironementChanger.h"
#include "Modules/ToggleSprintSneak.h"
#include "Modules/AutoGG.h"
#include "Modules/ChunkBorder.h"
#include "Modules/RenderOptions.h"


//Visual
#include "VisualModules/VisualTesting.h"
#include "VisualModules/Keystroke.h"
#include "VisualModules/frameCounter.h"
#include "VisualModules/clockModule.h"
#include "VisualModules/Coordinates.h"
#include "VisualModules/ServerModule.h"
#include "VisualModules/CPSmodule.h"
#include "VisualModules/Compass.h"
#include "VisualModules/SpeedCounter.h"
#include "VisualModules/ReachDisplay.h"
#include "VisualModules/ComboCounter.h"



Module ModuleManager::GetClickGuiModule(mltext("ClickGui", "Interface"), mltext("can be for the Clickgui or all the UIs\ncan also be Client General settings", "Peut être des réglages l'interface de Plasmic ou tout minecraft\nPeut aussi être des réglages généraux."));



void ModuleManager::InitModules() {

	//Modules
#ifndef NDEBUG
	moduleList.push_back(new TestModule);
#endif

	moduleList.push_back(new ZoomModule);
	moduleList.push_back(new Fullbright);
	moduleList.push_back(new FreeLook);
	moduleList.push_back(new EnvironementChanger);
	moduleList.push_back(new ToggleSprintSneak);
	moduleList.push_back(new AutoGG);
	moduleList.push_back(new ChunkBorder);
	moduleList.push_back(new RenderOptions);
       // moduleList.push_back(new );




	//Visual module
	//Visual module
	//Visual module
	//Visual module
	visualModuleList.push_back(new frameCounter);
	visualModuleList.push_back(new clockModule);
	visualModuleList.push_back(new Keystroke);
	visualModuleList.push_back(new Coordinates);
	visualModuleList.push_back(new ServerModule);
	visualModuleList.push_back(new CPSmodule);
	visualModuleList.push_back(new Compass);
	visualModuleList.push_back(new SpeedCounter);
	visualModuleList.push_back(new ReachDisplay);
	visualModuleList.push_back(new ComboCounter);
	//visualModuleList.push_back(new VisualTesting);

	
	//visualModuleList.push_back(new );
}

void ModuleManager::DeInit() {

	if (game::clickGui) {
		game::clickGui->onEject();
		delete game::clickGui;
	}

	//Modules
	for (int i = 0; i < moduleList.size(); i++) 
		if (moduleList[i] != nullptr) {
			if (moduleList[i]->isEnabled())
				moduleList[i]->onDisable();
			moduleList[i]->onEject();
			moduleList[i] = nullptr;
			delete moduleList[i];
		}
	//Visual modules
	for (int i = 0; i < visualModuleList.size(); i++)
		if (visualModuleList[i] != nullptr) {
			visualModuleList[i]->onDisable();
			visualModuleList[i]->onEject();
			visualModuleList[i] = nullptr;
			delete visualModuleList[i];
		}

}


Module* ModuleManager::getModuleByName(const char* NameOfTheModule) {
	for (int i = 0; i < moduleList.size(); i++)
		if (moduleList[i] != nullptr)
			if (!strcmp(moduleList[i]->name, NameOfTheModule))
				return moduleList[i];
	return nullptr;
}

void ModuleManager::BlockModuleByName(const char* NameOfTheModule) {
	for (int i = 0; i < moduleList.size(); i++)
		if (moduleList[i] != nullptr)
			if (!strcmp(moduleList[i]->name, NameOfTheModule)) {
				moduleList[i]->isBlocked = true;;
				moduleList[i]->Enable();
				return;
			}
}

VisualModule* ModuleManager::getVisualModuleByName(const char* NameOfTheModule) {
	for (int i = 0; i < visualModuleList.size(); i++)
		if (visualModuleList[i] != nullptr)
			if (!strcmp(visualModuleList[i]->name, NameOfTheModule))
				return visualModuleList[i];
	return nullptr;
}




extern bool doesPathExist(std::string path);
void Config::save(const char* name) {
	std::string precisePath = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Plasmic\\" + std::string(name) + std::string(".txt"));
	if (!doesPathExist(precisePath)) {
		std::filesystem::path p(precisePath);
		std::filesystem::create_directories(p.parent_path().string());
	}

	std::ofstream out(precisePath.c_str());

	out << "MODULE\n" << "ClickGui" << '\n' << ModuleManager::GetClickGuiModule.enabled << '\n';
	for (uint16_t j = 0; j < ModuleManager::GetClickGuiModule.settings.size(); j++)
		ModuleManager::GetClickGuiModule.settings[j].serialize(out);
	out << "ENDOFSETTING" << '\n';


	for (uint16_t i = 0; i < ModuleManager::moduleList.size(); i++) {
		out << "MODULE\n" << ModuleManager::moduleList[i]->name << '\n' << ModuleManager::moduleList[i]->enabled << '\n';
		for (uint16_t j = 0; j < ModuleManager::moduleList[i]->settings.size(); j++) 
			ModuleManager::moduleList[i]->settings[j].serialize(out);
	
		out << "ENDOFSETTING" << '\n';
	}

	for (uint16_t i = 0; i < ModuleManager::visualModuleList.size(); i++) {
		out << "VISUALMODULE\n" << ModuleManager::visualModuleList[i]->name << '\n' << ModuleManager::visualModuleList[i]->enabled << '\n';
		for (uint16_t j = 0; j < ModuleManager::visualModuleList[i]->settings.size(); j++) {
			ModuleManager::visualModuleList[i]->settings[j].serialize(out);
		}

		out << "ENDOFSETTING" << '\n';
	}

	out.close();
}


void Config::load(const char* name) {

	std::string precisePath = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Plasmic\\" + std::string(name) + std::string(".txt"));
	if (!doesPathExist(precisePath)) {
		std::filesystem::path p(precisePath);
		std::filesystem::create_directories(p.parent_path().string());
	}

	std::ifstream in(precisePath.c_str());
	if (!in.is_open()) 
		return;
	if (in.peek() == EOF)
		return;
	std::string mname;

	//load Clickgui
	std::getline(in, mname);
	if (!strcmp(mname.c_str(), "MODULE")) {
		std::getline(in, mname);
		if (strcmp(mname.c_str(), "ClickGui")) {
			in.close();
			in = std::ifstream(precisePath.c_str());
			if (!in.is_open())
				return;
		} else {
			bool sbe;
			in >> sbe;
			for (uint16_t k = 0;; k++) {
				in >> mname;
				if (!strcmp(mname.c_str(), "ENDOFSETTING"))
					break;

				bool found = false;
				for (uint16_t j = 0; j < ModuleManager::GetClickGuiModule.settings.size(); j++)
					if (!strcmp(mname.c_str(), ModuleManager::GetClickGuiModule.settings[j].internalName)) {
						found = true;
						ModuleManager::GetClickGuiModule.settings[j].deserialize(in);
					}
				if (!found) 
					std::getline(in, mname); //skip reading it as its not relevant anymore
			}
		}
	}


	while (in.peek() != EOF) {
		std::getline(in, mname);
		if (!strcmp(mname.c_str(),"MODULE")) {
			std::getline(in, mname);

			Module* md = ModuleManager::getModuleByName(mname.c_str());
			if (md == nullptr) {
				continue; //no module exist with this name, smh
				//Logf("nop gfdamslkfdas ganes");
			}
			bool sbe;
			in >> sbe;
			if (sbe)
				md->Enable();
			

			
			for (uint16_t k = 0;; k++) {
				in >> mname;
				if (!strcmp(mname.c_str(),"ENDOFSETTING"))
					break;

				bool found = false;
				for (uint16_t j = 0; j < md->settings.size(); j++) 
					if (!strcmp(mname.c_str(), md->settings[j].internalName)) {
						found = true;
					//	Logf("Deserializing %s    for %s", md->settings[j].internalName, md->name);
						md->settings[j].deserialize(in);
					}
				if (!found) {
					std::getline(in, mname); //skip reading it as its not relevant anymore
					//Logf("non.");
				}

			}

		} else if (!strcmp(mname.c_str(), "VISUALMODULE")) {
			std::getline(in, mname);
			VisualModule* md = ModuleManager::getVisualModuleByName(mname.c_str());
			if (md == nullptr) {
				//Logf("nop gfdamslkfdas ganes");
				continue; //no module exist with this name, smh
			}
			bool sbe;
			in >> sbe;
			if (sbe)
				md->Enable();
			//Logf("%s  %d", md->name, (int)sbe);


			for (uint16_t k = 0; k < md->settings.size(); k++) {
				in >> mname;
				if (!strcmp(mname.c_str(), "ENDOFSETTING"))
					break;

				bool found = false;
				for (uint16_t j = 0; j < md->settings.size(); j++)
					if (!strcmp(mname.c_str(), md->settings[j].internalName)) {
						found = true;
						//Logf("Deserializing %s    for %s", md->settings[j].internalName, md->name);
						md->settings[j].deserialize(in);
					}
				if (!found) {
					std::getline(in, mname); //skip reading it as its not relevant anymore
					//Logf("non.");
				}
			}

		}
		//else skip dis lyne
		//Logf("Skipping %s", mname.c_str());
	}


//	Logf("Finished loading config %s", name);
}


#include <thread>
extern void OnSecondTimerCalc();
void BlockModules() {
	std::string precisePath = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Plasmic\\Launcher\\Server.txt");
	std::ofstream out(precisePath.c_str());
	if (out.is_open()) 
		out.close();
	


	bool disabledModule = false;
	bool wasInMenu = true;
	char prevServer[64] = { 0 };
	RakNetInstance* raknetinst = 0;
	Sleep(250);
	while (raknetinst == NULL) {
		if (!mem::isRunning)
			return;
		raknetinst = game::clientinstance->minecraftGame->networkHandler->raknetInstance;
		Sleep(1);
	}

	while (mem::isRunning) {
		if (strcmp(prevServer, raknetinst->numericIP.getText()) || wasInMenu != (game::localPlayer == nullptr)) {


			memcpy(prevServer, raknetinst->numericIP.getText(), strlen(raknetinst->numericIP.getText()) + 1);
			//unblock all modules if he left the server
			if (!raknetinst->isonaServer()) {
				for (uint16_t i = 0; i < ModuleManager::moduleList.size(); i++)
					ModuleManager::moduleList[i]->isBlocked = false;
				if (disabledModule)
					ClickGui::sendNotificationf(mltext("Modules unblocked!", "Les modules ont été débloqué!"));
				disabledModule = false;
			}
			else
				if (strstr(raknetinst->serverTextIP.getText(), "hivebedrock")) {//if on the hive
					ModuleManager::BlockModuleByName("Freelook");
					ClickGui::sendNotificationf(mltext("Freelook will not be usable on this server.", "Freelook ne sera pas utilisable sur ce serveur."));
					disabledModule = true;
				}
				else if (strstr(raknetinst->serverTextIP.getText(), "nethergames")) {//if on the hive
					ModuleManager::BlockModuleByName("Freelook");
					ModuleManager::BlockModuleByName("Toggle Sprint/Sneak");
					ClickGui::sendNotificationf(mltext("Freelook and Toggle Sprint/Sneak will not be usable on this server.", "Freelook and Toggle Sprint/Sneak ne seront pas utilisable sur ce serveur."));
					disabledModule = true;
				}
				else if (strstr(raknetinst->serverTextIP.getText(), "galaxite")) {//if on galaxite
					ModuleManager::BlockModuleByName("Toggle Sprint/Sneak");
					ClickGui::sendNotificationf(mltext("Toggle Sprint/Sneak will not be usable on this server.", "Toggle Sprint/Sneak ne sera pas utilisable sur ce serveur."));
					disabledModule = true;
				}
				else if (strstr(raknetinst->serverTextIP.getText(), "mineplex")) {//if on mineplex
					ModuleManager::BlockModuleByName("Freelook");
					ClickGui::sendNotificationf(mltext("Freelook not be usable on this server.", "Freelook ne sera pas utilisable sur ce serveur."));
					disabledModule = true;
				}

			wasInMenu = (game::localPlayer == nullptr);
			std::string precisePath = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Plasmic\\Launcher\\Server.txt");
			std::ofstream out(precisePath.c_str());
			if (out.is_open()) {
				if (raknetinst->isonaServer())
					out << raknetinst->serverTextIP.getText();
				else if (!wasInMenu)
					out << "In a World";
				out.close();
			}
				

		
		}
		for (uint16_t i = 0; i < 1000; i++) {
			if (!mem::isRunning)
				return;
			OnSecondTimerCalc();
			Sleep(1);
		}
	}

}