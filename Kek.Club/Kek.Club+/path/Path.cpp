#include "Path.h"

#include "../../Utils/Logger.h"
#include "../../Utils/TimerUtils.h"
#include "../DrawUtils.h"
#include "../Module/ModuleManager.h"
Path::Path(const std::vector<PathSegment>& segments, bool isIncomplete) : segments(segments), isIncomplete(isIncomplete) {
}
Path::Path() : segments(), isIncomplete(false) {
}
void Path::draw(int highlight) const {
	for (int i = 0; i < segments.size(); i++) {
		auto seg = segments[i];
		int curIndex = -i * 75;
		DrawUtils::setColor(DrawUtils::getAstolfoRainbow(curIndex / 5, 1000).r, DrawUtils::getAstolfoRainbow(curIndex / 5, 1000).g, DrawUtils::getAstolfoRainbow(curIndex / 5, 1000).b, DrawUtils::getAstolfoRainbow(curIndex / 5, 1000).a);                                                                                                                                                                                                                                                      // Astolfo
		seg.draw();
	}
}
bool Path::isIncomplete1() const {
	return isIncomplete;
}
void Path::cutoff(float percentageKeep) {
	if (this->getNumSegments() == 0)
		return;
	int numKeep = (int)ceilf(this->getNumSegments() * percentageKeep);
	this->segments.erase(this->segments.begin() + numKeep, this->segments.end());
}
void Path::initPathSegments() {
	// Init segments
	for (auto& seg : segments) {
		seg.init();
	}

	// Check whether we can sprint or not
	if (segments.size() > 1) {
		for (int i = 0; i < segments.size() - 2; i++) {
			auto& curSeg = segments.at(i);
			auto& nextSeg = segments.at(i + 1);
			if (curSeg.getSegmentType() != PathSegmentType::WALK || nextSeg.getSegmentType() != PathSegmentType::WALK) {
				curSeg.setAllowSprint(true);
				continue;
			}
			if (curSeg.getStart().y != curSeg.getEnd().y) {
				curSeg.setAllowSprint(true);
				continue;
			}

			auto currentTangent = curSeg.getEnd().sub(curSeg.getStart()).toFloatVector().normalize();
			auto nextTangent = nextSeg.getEnd().sub(nextSeg.getStart()).toFloatVector().normalize();
			if (currentTangent.dot(nextTangent) > 0.3f) {  // make sure we're running in a similar direction
				curSeg.setAllowSprint(true);
			}
		}
	}

	this->isInitialized = true;
}
bool Path::isInitialized1() const {
	return isInitialized;
}