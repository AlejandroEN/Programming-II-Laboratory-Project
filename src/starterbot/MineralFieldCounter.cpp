#include "MineralFieldCounter.hpp"

void MineralFieldCounter::showMineralFielCounter()
{
	std::vector<int> NumeroDeMineralesAnterior;
	std::vector<int> Contadores;
	std::vector<int> FramesPorRecogida;
	std::vector<int> UltimoConteo;
	std::vector<std::vector<int>> veinteUltimosConteos;

	auto AllMinerals = BWAPI::Broodwar->getMinerals();

	int indice = 0;

	for (auto mineral : AllMinerals)
	{
		// Verificar si el recuento ha aumentado en un múltiplo de 8
		if ((mineral->getResources() - NumeroDeMineralesAnterior[indice]) != 0)
		{
			UltimoConteo[indice] = Contadores[indice];
			NumeroDeMineralesAnterior[indice] = mineral->getResources();
			// Reiniciar el contador de frames
			Contadores[indice] = 0;
			veinteUltimosConteos[indice].push_back(UltimoConteo[indice]);
			// Almacenar el último conteo antes de reiniciar el contador
		}
		else
		{
			// Incrementar el contador de frames
			Contadores[indice]++;
		}


		// Almacenar el recuento actual en la lista de últimos conteos


		// Mantener la lista de últimos 20 conteos
		if (veinteUltimosConteos[indice].size() > 20)
		{
			veinteUltimosConteos[indice].erase(veinteUltimosConteos[indice].begin());
		}

		// Calcular el promedio de los últimos 20 conteos
		int suma = 0;
		int promedio = 0;
		for (int count : veinteUltimosConteos[indice])
		{
			suma += count;
		}
		if (veinteUltimosConteos[indice].size() == 0)
		{
			promedio = 0;
		}
		else
		{
			promedio = suma / veinteUltimosConteos[indice].size();
		}
	}

	//auto Position = mineral->getPosition();
	//// Mostrar resultados en pantalla
	//BWAPI::Broodwar->drawTextMap(Position.x + 10, Position.y - 10, "Ultimo conteo:%d", UltimoConteo[indice]);
	//BWAPI::Broodwar->drawTextMap(Position.x + 10, Position.y, "Promedio:%d", promedio);


	indice++;
}
