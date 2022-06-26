#include "PathGoalXZ.h"

#include "../PathConstants.h"

bool PathGoalXZ::isInGoal(vec3_ti pos) {
	return pos.x == targetPos.x && pos.z == targetPos.z;
}
float PathGoalXZ::getHeuristicEstimation(vec3_ti pos) {
	return PathGoalXZ::heuristicEstimation(targetPos, pos);
}
float PathGoalXZ::heuristicEstimation(vec3_ti node, vec3_ti target) {
	vec3_ti diff = node.sub(target);
	int x = abs(diff.x);
	int z = abs(diff.z);
	float straight;
	float diagonal;
	if (x < z) {
		straight = (float)z - x;
		diagonal = (float)x;
	}
	else {
		straight = (float)x - z;
		diagonal = (float)z;
	}
	static const float SQRT_2 = sqrtf(2);
	diagonal *= SQRT_2;
	return (straight + diagonal) / SPRINT_SPEED;
}
PathGoalXZ::PathGoalXZ(const vec3_ti& targetPos) : targetPos(targetPos) {}