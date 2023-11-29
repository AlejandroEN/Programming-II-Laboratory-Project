#include "MineralFieldCounter.hpp"
#include <BWAPI.h>

void MineralFieldCounter::showMineralFieldCount()
{
    int currentPlayerMinerals = BWAPI::Broodwar->self()->minerals();

    // Verificar si el recuento ha aumentado en un múltiplo de 8
    if ((currentPlayerMinerals - mineralCount) != 0)
    {
        lastFrameCount = frameCounter;
        mineralCount = currentPlayerMinerals;
        // Reiniciar el contador de frames
        frameCounter = 0;
        lastCounts.push_back(lastFrameCount);
      // Almacenar el último conteo antes de reiniciar el contador
    }
    else 
    {
          // Incrementar el contador de frames
        frameCounter++;
    }


  // Almacenar el recuento actual en la lista de últimos conteos


  // Mantener la lista de últimos 20 conteos
  if (lastCounts.size() > 20)
  {
      lastCounts.erase(lastCounts.begin());
  }

  // Calcular el promedio de los últimos 20 conteos
  int sum = 0;
  for (int count : lastCounts)
  {
      sum += count;
  }

  int average = lastCounts.empty() ? 0 : sum / lastCounts.size();

  // Mostrar resultados en pantalla
  BWAPI::Broodwar->drawTextScreen(10, 0, "Frames contados: %d", frameCounter);
  BWAPI::Broodwar->drawTextScreen(10, 20, "Último conteo antes de reiniciar: %d", lastFrameCount);
  BWAPI::Broodwar->drawTextScreen(10, 40, "Últimos 20 conteos: ");

      for (int j = 0; j < lastCounts.size() &&j<5 ; j++) {
      BWAPI::Broodwar->drawTextScreen(10 + j * 20, 60 + 0 * 20, "%d, ", lastCounts[j]);
      }
      for (int j = 5; j < lastCounts.size() &&j<10 ; j++) {
          BWAPI::Broodwar->drawTextScreen(10 + (j-5) * 20, 60 + 1 * 20, "%d, ", lastCounts[j]);
      }
      for (int j = 10; j < lastCounts.size() && j<15 ; j++) {
          BWAPI::Broodwar->drawTextScreen(10 + (j-10) * 20, 60 + 2 * 20, "%d, ", lastCounts[j]);
      }
      for (int j = 15; j < lastCounts.size() ; j++) {
          BWAPI::Broodwar->drawTextScreen(10 + (j-15) * 20, 60 + 3 * 20, "%d, ", lastCounts[j]);
      }

  BWAPI::Broodwar->drawTextScreen(10, 140, "Promedio de los últimos 20 conteos: %d", average);
}