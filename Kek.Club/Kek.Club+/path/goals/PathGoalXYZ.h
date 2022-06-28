#pragma once

#include "PathGoal.h"
#include "PathGoalXZ.h"
#include "PathGoalY.h"

class PathGoalXYZ : public PathGoal {
private:
	vec3_ti targetPos;

public:
	PathGoalXYZ(const vec3_ti& targetPos);

	bool isInGoal(vec3_ti pos) override;
	float getHeuristicEstimation(vec3_ti pos) override;
};