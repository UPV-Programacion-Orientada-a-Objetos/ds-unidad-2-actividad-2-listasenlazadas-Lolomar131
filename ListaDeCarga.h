#ifndef LISTADECARGA_H
#define LISTADECARGA_H

#include "Nodo.h"
#include <iostream>

/**
 * @class ListaDeCarga
 * @brief Lista Doblemente Enlazada para almacenar los caracteres decodificados.
 * * Almacena el mensaje final en el orden correcto de procesamiento.
 */
class ListaDeCarga
{
private:
    Nodo* cabeza; ///< Puntero al primer nodo de la lista.
    Nodo* cola;   ///< Puntero al último nodo de la lista.

public:
    /**
     * @brief Constructor. Inicializa la lista vacía.
     */
    ListaDeCarga() : cabeza(nullptr), cola(nullptr) {}

    /**
     * @brief Destructor. Libera toda la memoria de los nodos creados con 'new'.
     */
    ~ListaDeCarga();

    /**
     * @brief Inserta un carácter decodificado al final de la lista.
     * @param dato El carácter decodificado a añadir.
     */
    void insertarAlFinal(char dato);

    /**
     * @brief Imprime el mensaje completo ensamblado en la consola.
     */
    void imprimirMensaje() const;
};

#endif // LISTADECARGA_H