#pragma once

#include <BWAPI.h>
#include <vector>

using namespace std;

// Segunda pregunta del proyecto
class MineralFieldTracker
{
	static inline vector<signed int> _mineralsAmount;
	static inline vector<signed int> _frameIntervals;
	static inline vector<signed int> _lastFrameIntervals;

	// Contiene los ultimos 20 intervalos
	// entre cada frame de recoleccion de
	// minerales.
	static inline vector<vector<signed int>> _frameIntervalsPerMineralField;

public:
	static void initializeFields();
	static void showMineralFieldCounter();
};