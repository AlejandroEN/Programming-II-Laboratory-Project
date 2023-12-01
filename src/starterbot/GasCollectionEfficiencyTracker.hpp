#pragma

#include <BWAPI.h>
#include <vector>

using namespace std;

// Tercera pregunta del proyecto
class GasCollectionEfficiencyTracker
{
	static inline vector<signed int> _gasesAmount;
	static inline vector<signed int> _frameIntervals;
	static inline vector<signed int> _lastFrameIntervals;
	static inline signed int _refineriesAmount = 0;

	// Contiene los ultimos 20 intervalos
	// entre cada frame de recolección de
	// gas.
	static inline vector<vector<signed int>> _frameIntervalsPerGasRefinery;

	static void initializeFields();

public:
	static void showCollectionCounter();	
};