#include "PathGoalY.h"

#include "../PathConstants.h"

PathGoalY::PathGoalY(float target) : target(target) {}
bool PathGoalY::isInGoal(vec3_ti pos) {
	return pos.y == target;
}
float PathGoalY::getHeuristicEstimation(vec3_ti pos) {
	return heuristicEstimation(pos, target);
}
float PathGoalY::heuristicEstimation(vec3_ti node, float target) {
	if (node.y > target)
		return FALL_N_BLOCKS_COST[(int)floorf(node.y - target)] * 0.99f;
	if (target > node.y)
		return (target - node.y) * JUMP_TIME * 0.99f;
	return 0;
}