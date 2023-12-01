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

	// Contiene los ultimos 20 intervalos
	// entre cada frame de recolección de
	// gas.
	static inline vector<vector<signed int>> _frameIntervalsPerGasRefinery;

public:
	static void initializeFields();
	static void showCollectionCounter();	
};