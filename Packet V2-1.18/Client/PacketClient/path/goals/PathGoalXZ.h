#pragma once

#include "PathGoal.h"

class PathGoalXZ : public PathGoal {
private:
	vec3_ti targetPos;
public:
	PathGoalXZ(const vec3_ti& targetPos);

	bool isInGoal(vec3_ti pos) override;
	float getHeuristicEstimation(vec3_ti pos) override;

	static float heuristicEstimation(vec3_ti node, vec3_ti target);
};