#pragma once

#include <vector>
#include "PathSegment.h"

class Path {
private:
	std::vector<PathSegment> segments;
	bool isIncomplete;
	bool isInitialized = 0;
public:
	Path(const std::vector<PathSegment>& segments, bool isIncomplete);
	Path();

	void cutoff(float percentageKeep);

	auto& getAllSegments() {
		return segments;
	}
	size_t getNumSegments() {
		return this->segments.size();
	}
	auto getSegment(size_t seg) {
		return this->segments[seg];
	}

	bool isInitialized1() const;
	void initPathSegments();
	bool isIncomplete1() const;
	void draw(int) const;
};