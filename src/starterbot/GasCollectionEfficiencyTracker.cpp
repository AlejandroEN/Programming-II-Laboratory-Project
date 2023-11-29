#include "GasCollectionEfficiencyTracker.hpp"

void GasCollectionEfficiencyTracker::showCollectionEfficiency()
{
	for (auto& unit : BWAPI::Broodwar->self()->getUnits())
	{
		if (unit->getType().isRefinery())
		{
			BWAPI::Broodwar->drawTextMap(unit->getPosition(), "Collection Efficiency: %f", getCollectionRate(unit) / 0.045f);
		}
	}
}

float GasCollectionEfficiencyTracker::getCollectionRate(BWAPI::Unit refinery)
{
	return 0;
}
