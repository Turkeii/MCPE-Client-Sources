#include "Path.h"
#include "../../Utils/DrawUtils.h"
#include "../../Utils/Logger.h"
#include "../../Utils/TimerUtil.h"
#include "../Module/ModuleManager.h"

Path::Path(const std::vector<PathSegment>& segments, bool isIncomplete) : segments(segments), isIncomplete(isIncomplete) {
}
Path::Path() : segments(), isIncomplete(false) {
}
void Path::draw(int highlight) const {
	for (int i = 0; i < segments.size(); i++) {
		auto seg = segments[i];
		int curIndex = -i * 75;
		auto interfaceMod = moduleMgr->getModule<Interface>();
		if (interfaceMod->color.getSelectedValue() == 0) DrawUtils::setColor(ColorUtil::rainbowColor(5, 1, 1, curIndex * 2).r, ColorUtil::rainbowColor(5, 1, 1, curIndex * 2).g, ColorUtil::rainbowColor(5, 1, 1, curIndex * 2).b, ColorUtil::rainbowColor(5, 1, 1, curIndex * 2).a); //Rainbow
		if (interfaceMod->color.getSelectedValue() == 1) DrawUtils::setColor(ColorUtil::astolfoRainbow(curIndex / 5, 1000).r, ColorUtil::astolfoRainbow(curIndex / 5, 1000).g, ColorUtil::astolfoRainbow(curIndex / 5, 1000).b, ColorUtil::astolfoRainbow(curIndex / 5, 1000).a); //Astolfo
		if (interfaceMod->color.getSelectedValue() == 2) DrawUtils::setColor(ColorUtil::waveColor(interfaceMod->r, interfaceMod->g, interfaceMod->b, interfaceMod->r2, interfaceMod->g2, interfaceMod->b2, curIndex * 2).r, ColorUtil::waveColor(interfaceMod->r, interfaceMod->g, interfaceMod->b, interfaceMod->r2, interfaceMod->g2, interfaceMod->b2, curIndex * 2).g, ColorUtil::waveColor(interfaceMod->r, interfaceMod->g, interfaceMod->b, interfaceMod->r2, interfaceMod->g2, interfaceMod->b2, curIndex * 2).b, ColorUtil::waveColor(interfaceMod->r, interfaceMod->g, interfaceMod->b, interfaceMod->r2, interfaceMod->g2, interfaceMod->b2, curIndex * 2).a); // Wave
		if (interfaceMod->color.getSelectedValue() == 3) DrawUtils::setColor(ColorUtil::RGBWave(interfaceMod->r, interfaceMod->g, interfaceMod->b, interfaceMod->r2, interfaceMod->g2, interfaceMod->b2, curIndex * 2).r, ColorUtil::RGBWave(interfaceMod->r, interfaceMod->g, interfaceMod->b, interfaceMod->r2, interfaceMod->g2, interfaceMod->b2, curIndex * 2).g, ColorUtil::RGBWave(interfaceMod->r, interfaceMod->g, interfaceMod->b, interfaceMod->r2, interfaceMod->g2, interfaceMod->b2, curIndex * 2).b, ColorUtil::RGBWave(interfaceMod->r, interfaceMod->g, interfaceMod->b, interfaceMod->r2, interfaceMod->g2, interfaceMod->b2, curIndex * 2).a); // Wave
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
			if (currentTangent.dot(nextTangent) > 0.3f) { // make sure we're running in a similar direction
				curSeg.setAllowSprint(true);
			}
		}
	}

	this->isInitialized = true;
}
bool Path::isInitialized1() const {
	return isInitialized;
}