#pragma once

#include <BWAPI.h>

// Segunda pregunta del proyecto
class MineralFieldTracker
{
	static inline std::vector<signed int> _numeroDeMineralesAnterior;
	static inline std::vector<signed int> _contadores;	
	static inline std::vector<signed int> _framesPorRecogida;
	static inline std::vector<signed int> _ultimoConteo;
	static inline std::vector<std::vector<signed int>> _veinteUltimosConteos;

public:
	static void showMineralFieldCounter();
};