#pragma once

#include <BWAPI.h>

// Primera pregunta del proyecto
class MineralIncrementTracker
{
	static inline signed int _mineralsAmount = 50;
	static inline signed int _frameCounter;
	static inline signed int _lastFrameCount;
	static inline signed int _lastCount = 50;
	static inline std::vector<signed int> _framesLastCounts;

public:
	static void showMineralFieldCount();
};
