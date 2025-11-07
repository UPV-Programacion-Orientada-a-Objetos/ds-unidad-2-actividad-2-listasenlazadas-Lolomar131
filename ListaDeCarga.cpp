#include "ListaDeCarga.h"
#include <cstdio>

ListaDeCarga::~ListaDeCarga()
{
    // Recorre y elimina cada nodo. ¡Vital para evitar memory leaks!
    Nodo* actual = cabeza;
    while (actual != nullptr)
    {
        Nodo* siguiente = actual->siguiente;
        delete actual; 
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
}

/**
 * @brief Inserta un carácter decodificado al final de la lista.
 * @param dato El carácter decodificado a añadir.
 */
void ListaDeCarga::insertarAlFinal(char dato)
{
    Nodo* nuevo = new Nodo(dato);
    if (cabeza == nullptr)
    {
        cabeza = nuevo;
        cola = nuevo;
    }
    else
    {
        nuevo->previo = cola;
        cola->siguiente = nuevo;
        cola = nuevo;
    }
}

/**
 * @brief Imprime el mensaje completo ensamblado.
 */
void ListaDeCarga::imprimirMensaje() const
{
    printf("\nMENSAJE OCULTO ENSAMBLADO:\n");
    Nodo* actual = cabeza;
    while (actual != nullptr)
    {
        putchar(actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}