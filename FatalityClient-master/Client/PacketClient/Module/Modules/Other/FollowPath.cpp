#include "FollowPath.h"

#include "../../../../Utils/Logger.h"
#include "../../ModuleManager.h"

using namespace std;
FollowPath::FollowPath() : IModule(0x0, Category::OTHER, "Path Moment") {}

const char* FollowPath::getModuleName() {
	return "FollowPath";
}

void FollowPath::startSearch(vec3_ti startNode, C_BlockSource* region, float searchTimeout, function<void(bool, Path)> callback) {
	if (pathFinder) {
		//auto notif = g_Data.addNotification("AutoPlay:", "Already searching!");
		//notif->isError = true;
		//notif->duration = 3.f;
		return;
	}
	pathFinder = make_shared<PathFinder>(startNode, region, goal);
	pathFinder->pathSearchTimeout = searchTimeout;
	auto ref = pathFinder;
	auto tempPath = pathFinder->findPath();
	pathFinder.reset();
	if (tempPath.getNumSegments() == 0 || !isEnabled()) {
		callback(false, tempPath);
		return;
	}
	callback(true, tempPath);
}

void FollowPath::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr || !g_Data.isInGame() || !g_Data.getLocalPlayer()->isAlive()) {
		setEnabled(false);
		return;
	}
	if (!goal) {
		setEnabled(false);
		return;
	}
	shouldStartSearch = true;
}

void FollowPath::onDisable() {
	shouldStartSearch = false;
	if (pathFinder)
		pathFinder->terminateSearch = true;
	engageDelay = -1;

	pathFinder.reset();
	path.reset();
	nextPath.reset();
	movementController.reset();
	goal.reset();
	if (moduleMgr->getModule<Flight>()->isEnabled())
		moduleMgr->getModule<Flight>()->setEnabled(false);
}

void FollowPath::onTick(C_GameMode* mode) {
	if (!shouldStartSearch)
		return;
	shouldStartSearch = false;

	C_LocalPlayer* player = g_Data.getLocalPlayer();
	auto pPos = player->eyePos0;
	vec3_ti startNode((int)floorf(pPos.x), (int)roundf(pPos.y - 1.62f), (int)floorf(pPos.z));

	startSearch(startNode, player->region, 0.5f, [&](bool succeeded, Path tempPath) {
		if (!succeeded) {
			//auto notif = g_Data.addNotification("AutoPlay:", "Could not find a path!");
			//notif->isError = true;
			//notif->duration = 3.f;
		}

		if (tempPath.isIncomplete1()) {
			//auto notif = g_Data.addNotification("AutoPlay:", "Found incomplete path!");
			//notif->isWarning = true;
			//notif->duration = 3.f;
		} else {
			//auto notif = g_Data.addNotification("AutoPlay:", "Found complete path!");
			//notif->isSuccess = true;
			//notif->duration = 3.f;
		}

		if (tempPath.isIncomplete1()) {
			tempPath.cutoff(0.9f);
		}
		engageDelay = 10;

		path = make_shared<Path>(tempPath.getAllSegments(), tempPath.isIncomplete1());
		movementController = make_unique<PathMovementController>(path);
		});
	if (moduleMgr->getModule<AutoPlay>()->server.getSelectedValue() == 2) {
		moduleMgr->getModule<Flight>()->mode.getSelectedValue() == 0;
		moduleMgr->getModule<Flight>()->speed = 0.21f;
		moduleMgr->getModule<Flight>()->value = 0.00f;
		if (!moduleMgr->getModule<Flight>()->isEnabled())
			moduleMgr->getModule<Flight>()->setEnabled(true);
		if (g_Data.getLocalPlayer()->isSprinting() && g_Data.getLocalPlayer()->velocity.magnitudexz() > 0.01f)
			g_Data.getLocalPlayer()->setSprinting(true);
	}
}

void FollowPath::onMove(C_MoveInputHandler* handler) {
	if (movementController) {
		movementController->step(g_Data.getLocalPlayer(), g_Data.getClientInstance()->getMoveTurnInput());
		if (engageDelay > 0)
			engageDelay--;

		if (movementController->isDone()) {
			if (movementController->getCurrentPath()->isIncomplete1()) {
				// Replace with next path if it exists
				if (nextPath && !pathFinder) {
					//auto notif = g_Data.addNotification("AutoPlay:", "Continuing on next path...");
					//notif->duration = 3.f;

					path = nextPath;
					nextPath.reset();
					movementController = make_unique<PathMovementController>(path);
				}
				else if (!pathFinder) {
					setEnabled(false);
				}
				else if (g_Data.getLocalPlayer()->isInWater()) {
					handler->isJumping = true;
				}
			}
		}
		else if (!pathFinder && engageDelay == 0 && path && path->isIncomplete1() && !nextPath) {
			engageDelay = 10;

			// Estimate time to completion
			auto curPath = movementController->getCurrentPath();
			float timeSpent = 0;
			if (curPath->getNumSegments() == 0) {
				setEnabled(false);
				return;
			}
			for (size_t i = curPath->getNumSegments() - 1; i > movementController->getCurrentPathSegment(); i--) {
				auto cur = curPath->getSegment(i);
				timeSpent += cur.getCost();
				if (timeSpent > 11)
					break;
			}

			if (timeSpent > 11)
				return;

			//auto notif = g_Data.addNotification("AutoPlay:", "Calculating next path...");
			//notif->duration = 3.f;

			float timeForSearch = clamp(timeSpent - 0.5f, 1.f, 3.f);
			auto lastSeg = curPath->getSegment(curPath->getNumSegments() - 1);
			nextPath.reset();
			startSearch(lastSeg.getEnd(), g_Data.getLocalPlayer()->region, timeForSearch, [&](bool succeeded, Path tempPath) {
				if (!succeeded) {
					//auto notif = g_Data.addNotification("AutoPlay:", "Could not find subsequent path!");
					//notif->isError = true;
					//notif->duration = 5.f;
				}

				if (tempPath.isIncomplete1()) {
					//auto notif = g_Data.addNotification("AutoPlay:", "Found subsequent incomplete path!");
					//notif->isWarning = true;
					//notif->duration = 3.f;
				} else {
					//auto notif = g_Data.addNotification("AutoPlay:", "Found subsequent complete path!");
					//notif->isSuccess = true;
					//notif->duration = 3.f;
				}

				if (tempPath.isIncomplete1()) {
					tempPath.cutoff(0.9f);
				}

				nextPath = make_shared<Path>(tempPath.getAllSegments(), tempPath.isIncomplete1());
				});
		}
	}
}
void FollowPath::onLevelRender() {
	if (!g_Data.isInGame() || g_Data.getLocalPlayer() == nullptr) {
		setEnabled(false);
		return;
	}

	if (movementController && path)
		path->draw(movementController->getCurrentPathSegment());
}