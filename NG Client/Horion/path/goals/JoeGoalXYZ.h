#pragma once

#include "JoeGoal.h"
#include "JoeGoalY.h"
#include "JoeGoalXZ.h"

class JoeGoalXYZ : public JoeGoal {
private:
	vec3i targetPos;
public:
	JoeGoalXYZ(const vec3i& targetPos);

	bool isInGoal(vec3i pos) override;
	float getHeuristicEstimation(vec3i pos) override;
};
