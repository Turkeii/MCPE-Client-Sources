#pragma once
#include "../../../path/PathMovementController.h"
#include "../../../path/goals/PathGoal.h"
#include "../../../path/PathFinder.h"
#include "../Module.h"
#include <functional>

class FollowPath : public IModule {
public:
	std::shared_ptr<PathGoal> goal;
	std::shared_ptr<PathFinder> pathFinder;
	std::unique_ptr<PathMovementController> movementController;
	std::shared_ptr<Path> path;
	std::shared_ptr<Path> nextPath;
	bool shouldStartSearch = false;
	int engageDelay = -1;

	void startSearch(vec3_ti startNode, C_BlockSource* region, float searchTimeout, std::function<void(bool, Path)> callback);
	void onMove(C_MoveInputHandler* handler) override;
	void onTick(C_GameMode* mode) override;
	const char* getModuleName() override;
	void onLevelRender() override;
	void onDisable() override;
	void onEnable() override;
	FollowPath();
};