#include "MineralFieldTracker.hpp"

void MineralFieldTracker::initializeFields()
{
	vector<int> _;
	auto& minerals = BWAPI::Broodwar->getMinerals();

	for (auto mineral : minerals)
	{
		_mineralsAmount.push_back(mineral->getResources());
		_frameIntervals.push_back(0);
		_lastFrameIntervals.push_back(0);
	    _frameIntervalsPerMineralField.push_back(_);
	}
}

void MineralFieldTracker::showMineralFieldCounter()
{
	signed int mineralIndex = 0, sum;
	float average;
	BWAPI::Position mineralFieldPosition;

	for (auto mineralField : BWAPI::Broodwar->getMinerals())
	{
		sum = 0;

		if (mineralField->getResources() - _mineralsAmount[mineralIndex] != 0)
		{
			_lastFrameIntervals[mineralIndex] = _frameIntervals[mineralIndex];
			_mineralsAmount[mineralIndex] = mineralField->getResources();

			// Reiniciamos el contador de frames para el mineral field de la iteración actual
			_frameIntervals[mineralIndex] = 0;
			_frameIntervalsPerMineralField[mineralIndex].push_back(_lastFrameIntervals[mineralIndex]);
		}
		else
		{
			// Incrementamos el contador de frames para cada mineral field
			_frameIntervals[mineralIndex]++;
		}

		if (_frameIntervalsPerMineralField[mineralIndex].size() > 20)
		{
			_frameIntervalsPerMineralField[mineralIndex].erase(_frameIntervalsPerMineralField[mineralIndex].begin());
		}

		// Calcular el promedio de los ultimos 20 conteos
		for (int count : _frameIntervalsPerMineralField[mineralIndex])
		{
			sum += count;
		}

		if (_frameIntervalsPerMineralField[mineralIndex].size() == 0)
		{
			average = 0;
		}
		else
		{
			average = sum / _frameIntervalsPerMineralField[mineralIndex].size();
		}

		mineralFieldPosition = mineralField->getPosition();

		// Mostrar resultados en pantalla
		BWAPI::Broodwar->drawTextMap(mineralFieldPosition.x - 20,
									 mineralFieldPosition.y - 10,
									 "Ultimo conteo:%d", 
									 _lastFrameIntervals[mineralIndex]);

		BWAPI::Broodwar->drawTextMap(mineralFieldPosition.x - 20,
									 mineralFieldPosition.y,
									 "Promedio:%f", 
									 average);
		mineralIndex++;
	}
}


