#pragma once

#include "PathGoal.h"

class PathGoalY : public PathGoal {
private:
	float target;
public:
	PathGoalY(float target);

	bool isInGoal(vec3_ti pos) override;
	float getHeuristicEstimation(vec3_ti pos) override;

	static float heuristicEstimation(vec3_ti node, float target);
};