#pragma once

#include "../../Utils/HMath.h"
#include "Path.h"
#include "PathSegment.h"
#include "goals/PathGoal.h"
#include "../../SDK/CBlockLegacy.h"
#include "PathConstants.h"
#include <memory>

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