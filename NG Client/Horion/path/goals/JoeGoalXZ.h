#pragma once

#include "JoeGoal.h"

class JoeGoalXZ : public JoeGoal{
private:
	vec3i targetPos;
public:
	JoeGoalXZ(const vec3i& targetPos);

	bool isInGoal(vec3i pos) override;
	float getHeuristicEstimation(vec3i pos) override;

	static float heuristicEstimation(vec3i node, vec3i target);
};
