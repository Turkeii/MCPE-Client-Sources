#pragma once

#include "../../../Utils/HMath.h"

class JoeGoal {
private:
public:
	virtual ~JoeGoal();

	virtual bool isInGoal(vec3i pos) = 0;
	virtual float getHeuristicEstimation(vec3i pos) = 0;
};
