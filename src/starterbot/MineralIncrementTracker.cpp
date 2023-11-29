#include "MineralIncrementTracker.hpp"

void MineralIncrementTracker::showMineralFieldCount()
{
	signed int framesCountSum = 0;
	signed const int currentMineralsAmount = BWAPI::Broodwar->self()->minerals();

	// Verificar si el recuento ha aumentado en un multiplo de 8
	if (currentMineralsAmount - _mineralsAmount != 0)
	{
		_lastFrameCount = _frameCounter;
		_mineralsAmount = currentMineralsAmount;
		_frameCounter = 0;
		_framesLastCounts.push_back(_lastFrameCount);
	}
	else
	{
		_frameCounter++;
	}

	if (_framesLastCounts.size() > 20)
	{
		_framesLastCounts.erase(_framesLastCounts.begin());
	}

	// Calcular el promedio de los ultimos 20 conteos
	for (const auto count : _framesLastCounts)
	{
		framesCountSum += count;
	}

	const float framesCountAverage = _framesLastCounts.empty() ? 0 : static_cast<float>(framesCountSum) / static_cast<float>(_framesLastCounts.size());

	// Mostrar resultados en pantalla
	BWAPI::Broodwar->drawTextScreen(10, 0, "Frames contados: %d", _frameCounter);
	BWAPI::Broodwar->drawTextScreen(10, 20, "Ultimo conteo antes de reiniciar: %d", _lastFrameCount);
	BWAPI::Broodwar->drawTextScreen(10, 40, "Ultimos 20 conteos: ");

	for (int j = 0; j < _framesLastCounts.size() && j < 5 ; j++)
	{
		BWAPI::Broodwar->drawTextScreen(10 + j * 20, 60 + 0 * 20, "%d, ", _framesLastCounts[j]);
	}

	for (int j = 5; j < _framesLastCounts.size() && j < 10 ; j++)
	{
		BWAPI::Broodwar->drawTextScreen(10 + (j-5) * 20, 60 + 1 * 20, "%d, ", _framesLastCounts[j]);
	}

	for (int j = 10; j < _framesLastCounts.size() && j < 15 ; j++)
	{
		BWAPI::Broodwar->drawTextScreen(10 + (j - 10) * 20, 60 + 2 * 20, "%d, ", _framesLastCounts[j]);
	}

	for (int j = 15; j < _framesLastCounts.size() ; j++)
	{
		BWAPI::Broodwar->drawTextScreen(10 + (j-15) * 20, 60 + 3 * 20, "%d, ", _framesLastCounts[j]);
	}

	BWAPI::Broodwar->drawTextScreen(10, 140, "Promedio de los ultimos 20 conteos: %f;", framesCountAverage);
}
