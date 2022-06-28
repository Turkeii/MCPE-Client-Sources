#pragma once

#include <functional>

#include "../../path/PathFinder.h"
#include "../../path/PathMovementController.h"
#include "../../path/goals/PathGoal.h"
#include "Module.h"

class FollowPath : public IModule {
public:
	std::shared_ptr<PathGoal> goal;
	std::shared_ptr<PathFinder> pathFinder;
	std::unique_ptr<PathMovementController> movementController;
	std::shared_ptr<Path> path;
	std::shared_ptr<Path> nextPath;
	bool shouldStartSearch = false;
	int engageDelay = -1;

	FollowPath();

	const char* getModuleName() override;
	void startSearch(vec3_ti startNode, C_BlockSource* region, float searchTimeout, std::function<void(bool, Path)> callback);
	void onTick(C_GameMode* mode) override;
	void onEnable() override;
	void onDisable() override;
	void onLevelRender() override;
	void onMove(C_MoveInputHandler* handler) override;
};