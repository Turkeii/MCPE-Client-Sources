#include <Windows.h>

#include <chrono>
#include <ctime>
#include <iostream>

#include "../Utils/Logger.h"
#include "TimerUtils.h"

__int64 lastMS = TimerUtils::getCurrentMs();
__int64 ms;
__int64 prevMS = 0;
__int64 timeMS = -1;

__int64 TimerUtils::getCurrentMs() {
	FILETIME f;
	GetSystemTimeAsFileTime(&f);
	(long long)f.dwHighDateTime;
	__int64 nano = ((__int64)f.dwHighDateTime << 32LL) + (__int64)f.dwLowDateTime;
	return (nano - 116444736000000000LL) / 10000;
}

bool TimerUtils::hasTimePassed(__int64 ms) {
	return getCurrentMs() >= timeMS + ms;
}

__int64 TimerUtils::getTime() {
	return getCurrentMs();
}

void TimerUtils::reset2() {
	prevMS = getTime();
}

__int64 TimerUtils::getDifference() {
	return getTime() - prevMS;
}

void TimerUtils::setDifference(__int64 difference) {
	prevMS = getTime() - difference;
}

void TimerUtils::resetTime() {
	lastMS = getCurrentMs();
	timeMS = getCurrentMs();
}

__int64 TimerUtils::getElapsedTime1() {
	return (getCurrentMs() - timeMS);
}

bool TimerUtils::hasTimedElapsed(__int64 time, bool reset) {
	if (getCurrentMs() - lastMS > time) {
		if (reset)
			resetTime();
		return true;
	}
	return false;
}

void TimerUtils::reset1() {
	ms = getCurrentMs();
}

bool TimerUtils::elapsed(__int64 milliseconds) {
	return (getCurrentMs() - ms) > milliseconds;
}

__int64 TimerUtils::getElapsedTime() {
	return getCurrentMs() - ms;
}