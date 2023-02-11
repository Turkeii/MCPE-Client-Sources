#pragma once

#include "Path.h"
#include "../../SDK/CEntity.h"
#include "../../SDK/CMoveInputHandler.h"

class PathMovementController {
private:
	std::shared_ptr<Path> currentPath;
	struct {
		int currentPathSegment = 0;
		bool recoverToStartPos = false;

		void nextSegment() {
			currentPathSegment++;
			recoverToStartPos = false;
		}
	} stateInfo;

public:
	bool overrideViewAngles = false;
	vec2_t targetViewAngles = { 0, 0 };

	PathMovementController(std::shared_ptr<Path> path);

	void step(C_LocalPlayer* player, C_MoveInputHandler* movementHandler);
	bool isDone() {
		return stateInfo.currentPathSegment >= currentPath->getNumSegments();
	}
	int getCurrentPathSegment() const;
	const std::shared_ptr<Path>& getCurrentPath() const;
};