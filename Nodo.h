#ifndef NODO_H
#define NODO_H

/**
 * @struct Nodo
 * @brief Estructura base para las listas.
 * * Contiene un dato tipo char y punteros para listas doblemente enlazadas.
 */
struct Nodo
{
    char dato; ///< El carácter de datos que se almacena.
    Nodo* siguiente; ///< Puntero al nodo siguiente.
    Nodo* previo;    ///< Puntero al nodo previo.

    /**
     * @brief Constructor del Nodo.
     * @param val El carácter a guardar.
     */
    Nodo(char val) : dato(val), siguiente(nullptr), previo(nullptr) {}
};

#endif // NODO_H