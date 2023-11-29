#include "MineralFieldTracker.hpp"

void MineralFieldTracker::initializeFields()
{
	std::vector<int> veinte;
	auto minerals = BWAPI::Broodwar->getMinerals();
	for (auto mineral : minerals)
	{
		_numeroDeMineralesAnterior.push_back(mineral->getResources());
		_contadores.push_back(0);
		_framesPorRecogida.push_back(0);
		_ultimoConteo.push_back(0);
		_veinteUltimosConteos.push_back(veinte);
	}
}

void MineralFieldTracker::showMineralFieldCounter()
{
	const auto minerals = BWAPI::Broodwar->getMinerals();
	signed int mineralIndex = 0, suma = 0;
	float promedio = 0;

	for (auto mineral : minerals)
	{
		if (mineral->getResources() - _numeroDeMineralesAnterior[mineralIndex] != 0)
		{
			_ultimoConteo[mineralIndex] = _contadores[mineralIndex];
			_numeroDeMineralesAnterior[mineralIndex] = mineral->getResources();
			// Reiniciar el contador de frames
			_contadores[mineralIndex] = 0;
			_veinteUltimosConteos[mineralIndex].push_back(_ultimoConteo[mineralIndex]);
		}
		else
		{
			// Incrementar el contador de frames
			_contadores[mineralIndex]++;
		}

		if (_veinteUltimosConteos[mineralIndex].size() > 20)
		{
			_veinteUltimosConteos[mineralIndex].erase(_veinteUltimosConteos[mineralIndex].begin());
		}

		// Calcular el promedio de los ultimos 20 conteos
		for (int count : _veinteUltimosConteos[mineralIndex])
		{
			suma += count;
		}

		if (_veinteUltimosConteos[mineralIndex].size() == 0)
		{
			promedio = 0;
		}
		else
		{
			promedio = suma / _veinteUltimosConteos[mineralIndex].size();
		}

		auto position = mineral->getPosition();

		// Mostrar resultados en pantalla
		BWAPI::Broodwar->drawTextMap(position.x + 10, position.y - 10, "Ultimo conteo:%d", _ultimoConteo[mineralIndex]);
		BWAPI::Broodwar->drawTextMap(position.x + 10, position.y, "Promedio:%f", promedio);
		mineralIndex++;
	}
}


