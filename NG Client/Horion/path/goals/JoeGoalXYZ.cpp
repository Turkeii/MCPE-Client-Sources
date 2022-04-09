#include "JoeGoalXYZ.h"
bool JoeGoalXYZ::isInGoal(vec3i pos) {
	return pos == targetPos;
}
float JoeGoalXYZ::getHeuristicEstimation(vec3i pos) {
	return JoeGoalXZ::heuristicEstimation(pos, targetPos) + JoeGoalY::heuristicEstimation(pos, (float)targetPos.y);
}
JoeGoalXYZ::JoeGoalXYZ(const vec3i& targetPos) : targetPos(targetPos) {}
