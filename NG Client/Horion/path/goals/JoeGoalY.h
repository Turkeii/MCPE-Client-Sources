#pragma once

#include "JoeGoal.h"

class JoeGoalY : public JoeGoal {
private:
	float target;
public:
	JoeGoalY(float target);

	bool isInGoal(vec3i pos) override;
	float getHeuristicEstimation(vec3i pos) override;

	static float heuristicEstimation(vec3i node, float target);
};
