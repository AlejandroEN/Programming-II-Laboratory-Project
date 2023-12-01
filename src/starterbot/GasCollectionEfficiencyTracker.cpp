#include "GasCollectionEfficiencyTracker.hpp"

void GasCollectionEfficiencyTracker::initializeFields()
{
	vector<int> _;
	auto& gases = BWAPI::Broodwar->getGeysers();

	for (auto gas : gases)
	{
		_gasesAmount.push_back(gas->getResources());
		_frameIntervals.push_back(0);
		_lastFrameIntervals.push_back(0);
		_frameIntervalsPerGasRefinery.push_back(_);
	}
}

void GasCollectionEfficiencyTracker::showCollectionCounter()
{
	signed int gasIndex = 0, sum = 0;
	float average;
	BWAPI::Position gasRefineryPosition;

	for (auto gasRefinery : BWAPI::Broodwar->getAllUnits())
	{
		if (!gasRefinery->getType().isRefinery())
		{
			continue;
		}

		if (gasRefinery->getResources() - _gasesAmount[gasIndex] != 0)
		{
			_lastFrameIntervals[gasIndex] = _frameIntervals[gasIndex];
			_gasesAmount[gasIndex] = gasRefinery->getResources();

			// Reiniciamos el contador de frames para el mineral field de la iteración actual
			_frameIntervals[gasIndex] = 0;
			_frameIntervalsPerGasRefinery[gasIndex].push_back(_lastFrameIntervals[gasIndex]);
		}
		else
		{
			// Incrementamos el contador de frames para cada mineral field
			_frameIntervals[gasIndex]++;
		}

		if (_frameIntervalsPerGasRefinery[gasIndex].size() > 20)
		{
			_frameIntervalsPerGasRefinery[gasIndex].erase(_frameIntervalsPerGasRefinery[gasIndex].begin());
		}

		// Calcular el promedio de los ultimos 20 conteos
		for (int count : _frameIntervalsPerGasRefinery[gasIndex])
		{
			sum += count;
		}

		if (_frameIntervalsPerGasRefinery[gasIndex].size() == 0)
		{
			average = 0;
		}
		else
		{
			average = sum / _frameIntervalsPerGasRefinery[gasIndex].size();
		}

		gasRefineryPosition = gasRefinery->getPosition();

		BWAPI::Broodwar->drawTextMap(gasRefineryPosition.x, gasRefineryPosition.y, "Average: %f", average);

		sum = 0;
		gasIndex++;
	}
}
