#pragma once

#include <memory>

#include "../../SDK/CBlockLegacy.h"
#include "../../Utils/HMath.h"
#include "Path.h"
#include "PathConstants.h"
#include "PathSegment.h"
#include "goals/PathGoal.h"

class PathFinder {
private:
	vec3_ti startPos;
	Path currentPath;
	C_BlockSource* region;
	std::shared_ptr<PathGoal> goal;

public:
	bool terminateSearch = false;
	float pathSearchTimeout = 5.f;

	PathFinder(vec3_ti start, C_BlockSource* reg, std::shared_ptr<PathGoal> goal);

	Path findPath();
	const Path& getCurrentPath() const;
};