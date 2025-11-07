#include "SerialSim.h"
#include <cstdio>

SerialSim::SerialSim() : indice_trama_actual(0) 
{
    printf("Iniciando Decodificador PRT-7. Conexión Serial Simulada.\n");
    printf("Esperando tramas...\n\n");
}

const char* SerialSim::leerSiguienteTrama()
{
    // Verifica si hemos llegado al final de la secuencia
    if (tramas[indice_trama_actual] == nullptr)
    {
        return nullptr;
    }
    
    // Devuelve la trama actual y avanza el índice
    return tramas[indice_trama_actual++];
}