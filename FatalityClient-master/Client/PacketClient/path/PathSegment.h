#pragma once

#include "../../Utils/HMath.h"
#include <vector>

enum PathSegmentType {
	INVALID = -1,
	WALK = 0,
	JUMP,
	DROP,
	PARKOUR_JUMP_SINGLE,
	WATER_WALK
};

class PathSegment {
private:
	PathSegmentType segmentType;
	vec3_ti start, end;
	float cost;
	bool allowSprint;
	std::vector<vec3_ti> validPositions;
public:
	PathSegment(PathSegmentType type, vec3_ti& start, vec3_ti& stop, float cost, bool allowSprint = false);
	void draw();
	bool isAllowingSprint() const;
	void setAllowSprint(bool allowSprint);
	PathSegmentType getSegmentType() const;
	const vec3_ti& getStart() const;
	const vec3_ti& getEnd() const;
	bool isInValidPosition(const vec3_ti& pos) const;
	void setValidPositions(const std::vector<vec3_ti>& validPositions);
	float getCost() const;
	void init();
};