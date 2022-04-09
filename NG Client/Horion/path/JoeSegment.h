#pragma once

#include "../../Utils/HMath.h"
#include <vector>

enum JoeSegmentType{
	INVALID = -1,
	WALK = 0,
	JUMP,
	DROP,
	PARKOUR_JUMP_SINGLE,
	WATER_WALK
};

class JoeSegment {
private:
	JoeSegmentType segmentType;
	vec3i start, end;
	float cost;
	bool allowSprint;
	std::vector<vec3i> validPositions;
public:
	JoeSegment(JoeSegmentType type, vec3i& start, vec3i& stop, float cost, bool allowSprint = false);
	void draw();
	bool isAllowingSprint() const;
	void setAllowSprint(bool allowSprint);
	JoeSegmentType getSegmentType() const;
	const vec3i& getStart() const;
	const vec3i& getEnd() const;
	bool isInValidPosition(const vec3i& pos) const;
	void setValidPositions(const std::vector<vec3i>& validPositions);
	float getCost() const;
	void init();
};
