#include "TramaBase.h"
#include <cstdio>

// ----------------------------------------------------
// TramaLoad
// ----------------------------------------------------
TramaLoad::TramaLoad(char f) : fragmento(f) {}
TramaLoad::~TramaLoad() {} 

/**
 * @brief Decodifica el fragmento usando el rotor y lo añade a la lista de carga.
 */
void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor)
{
    // 1. Decodificar
    char decodificado = rotor->getMapeo(this->fragmento);

    // 2. Insertar resultado
    carga->insertarAlFinal(decodificado);

    printf("Trama recibida: [L,%c] -> Procesando... -> Fragmento '%c' decodificado como '%c'.\n", 
           this->fragmento, this->fragmento, decodificado);
}

// ----------------------------------------------------
// TramaMap
// ----------------------------------------------------
TramaMap::TramaMap(int n) : N(n) {}
TramaMap::~TramaMap() {} 

/**
 * @brief Ejecuta la rotación del rotor.
 */
void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor)
{
    // 1. Rotar el rotor
    rotor->rotar(this->N);

    printf("Trama recibida: [M,%d] -> Procesando... -> ROTANDO ROTOR %s%d.\n", 
           this->N, (this->N > 0 ? "+" : ""), this->N);
}