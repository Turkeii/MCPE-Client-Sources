#include "JoeGoalXZ.h"

#include "../JoeConstants.h"

bool JoeGoalXZ::isInGoal(vec3i pos) {
	return pos.x == targetPos.x && pos.z == targetPos.z;
}
float JoeGoalXZ::getHeuristicEstimation(vec3i pos) {
	return JoeGoalXZ::heuristicEstimation(targetPos, pos);
}
float JoeGoalXZ::heuristicEstimation(vec3i node, vec3i target) {
	vec3i diff = node.sub(target);
	int x = abs(diff.x);
	int z = abs(diff.z);
	float straight;
	float diagonal;
	if (x < z) {
		straight = (float)z - x;
		diagonal = (float)x;
	} else {
		straight = (float)x - z;
		diagonal = (float)z;
	}
	static const float SQRT_2 = sqrtf(2);
	diagonal *= SQRT_2;
	return (straight + diagonal) / SPRINT_SPEED;
}
JoeGoalXZ::JoeGoalXZ(const vec3i& targetPos) : targetPos(targetPos) {}
