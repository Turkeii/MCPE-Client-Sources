#include "PathGoalXYZ.h"
bool PathGoalXYZ::isInGoal(vec3_ti pos) {
	return pos == targetPos;
}
float PathGoalXYZ::getHeuristicEstimation(vec3_ti pos) {
	return PathGoalXZ::heuristicEstimation(pos, targetPos) + PathGoalY::heuristicEstimation(pos, (float)targetPos.y);
}
PathGoalXYZ::PathGoalXYZ(const vec3_ti& targetPos) : targetPos(targetPos) {}