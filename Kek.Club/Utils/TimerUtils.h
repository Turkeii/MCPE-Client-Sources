#pragma once

class TimerUtils {
public:
	static __int64 getCurrentMs();
	static bool hasTimePassed(__int64 ms);
	// static __int64 hasTimeLeft(__int64 ms);
	static void reset2();
	static __int64 getDifference();
	static void setDifference(__int64 difference);
	static void resetTime();
	static __int64 getElapsedTime1();
	static bool hasTimedElapsed(__int64 time, bool reset);
	static void reset1();
	static bool elapsed(__int64 ms);
	static __int64 getTime();
	static __int64 getElapsedTime();
};