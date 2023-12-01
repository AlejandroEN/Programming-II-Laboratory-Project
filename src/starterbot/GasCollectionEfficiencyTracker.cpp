#include "GasCollectionEfficiencyTracker.hpp"

void GasCollectionEfficiencyTracker::initializeFields()
{
	signed int refineriesAmount = 0;

	for (auto refinery : BWAPI::Broodwar->getAllUnits())
	{
		if (refinery->getType().isRefinery())
		{
			refineriesAmount++;

			if (refineriesAmount != _refineriesAmount)
			{
				_refineriesAmount++;
				vector<int> _;
				_gasesAmount.push_back(5000); // aquí el error
				_frameIntervals.push_back(0);
				_lastFrameIntervals.push_back(0);
				_frameIntervalsPerGasRefinery.push_back(_);
			}
		}
	}
}

void GasCollectionEfficiencyTracker::showCollectionCounter()
{
	initializeFields();

	signed int gasIndex = 0, sum;
	float average;
	BWAPI::Position gasRefineryPosition;

	for (auto gasRefinery : BWAPI::Broodwar->getAllUnits())
	{
		if (!gasRefinery->getType().isRefinery())
		{
			continue;
		}

		sum = 0;

		if (gasRefinery->getResources() - _gasesAmount[gasIndex] != 0)
		{
			_lastFrameIntervals[gasIndex] = _frameIntervals[gasIndex];
			_gasesAmount[gasIndex] = gasRefinery->getResources();

			// Reiniciamos el contador de frames para el mineral field de la iteraci�n actual
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

		BWAPI::Broodwar->drawTextMap(gasRefineryPosition.x - 20,
									 gasRefineryPosition.y - 10,
									 "Frames contados: %d",
									 _lastFrameIntervals[gasIndex]);

		BWAPI::Broodwar->drawTextMap(gasRefineryPosition.x - 20,
									 gasRefineryPosition.y,
									 "Average: %f",
									 average);
	}
}
