#pragma

#include <BWAPI.h>

// Tercera pregunta del proyecto
class GasCollectionEfficiencyTracker
{
private:
	signed int _framesCount;


public:
	float getCollectionRate(BWAPI::Unit refinery);
	void showCollectionEfficiency();	
};