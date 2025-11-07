#ifndef ROTORDEMAPEO_H
#define ROTORDEMAPEO_H

#include "Nodo.h"
#include <cstdio>

/**
 * @class RotorDeMapeo
 * @brief Lista Circular Doblemente Enlazada que actúa como el "disco de cifrado".
 * * Contiene el alfabeto (A-Z, espacio) y gestiona la rotación del punto de inicio.
 */
class RotorDeMapeo
{
private:
    Nodo* cabeza; ///< Puntero al inicio lógico actual (la posición '0' del rotor).

    /**
     * @brief Crea los 27 nodos (A-Z y espacio) y los enlaza circularmente.
     */
    void inicializarRotor();

public:
    /**
     * @brief Constructor. Inicializa el rotor con A-Z, cabeza en 'A'.
     */
    RotorDeMapeo();

    /**
     * @brief Destructor. Rompe el círculo y libera toda la memoria de los nodos.
     */
    ~RotorDeMapeo();

    /**
     * @brief Rota el puntero 'cabeza' N posiciones.
     * @param N Número de rotaciones (positivo=adelante, negativo=atrás).
     */
    void rotar(int N);

    /**
     * @brief Decodifica un carácter de entrada según la rotación actual.
     * * Implementa la lógica de Rueda de César inversa moviendo punteros.
     * @param in El carácter codificado (fragmento de la TramaLoad).
     * @return El carácter decodificado.
     */
    char getMapeo(char in);
};

#endif // ROTORDEMAPEO_H