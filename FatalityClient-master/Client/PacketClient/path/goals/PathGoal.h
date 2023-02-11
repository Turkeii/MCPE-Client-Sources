#pragma once

#include "../../../Utils/HMath.h"

class PathGoal {
private:
public:
	virtual ~PathGoal();

	virtual bool isInGoal(vec3_ti pos) = 0;
	virtual float getHeuristicEstimation(vec3_ti pos) = 0;
};