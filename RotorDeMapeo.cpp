#include "RotorDeMapeo.h"
#include <cmath> 
#include <cstdlib> 

RotorDeMapeo::RotorDeMapeo() : cabeza(nullptr)
{
    inicializarRotor();
}

/**
 * @brief Crea los 27 nodos (A-Z y espacio) y los enlaza circularmente.
 */
void RotorDeMapeo::inicializarRotor()
{
    const char* alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

    cabeza = new Nodo(alfabeto[0]);
    Nodo* ultimo = cabeza;

    for (int i = 1; i < 27; ++i)
    {
        Nodo* nuevo = new Nodo(alfabeto[i]);
        nuevo->previo = ultimo;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }

    cabeza->previo = ultimo;
    ultimo->siguiente = cabeza;

    printf("RotorDeMapeo inicializado con 27 caracteres (A-Z, Espacio).\n");
}

RotorDeMapeo::~RotorDeMapeo()
{
    if (cabeza == nullptr) return;

    Nodo* actual = cabeza->siguiente;
    cabeza->previo->siguiente = nullptr; // Romper el círculo para la eliminación
    
    while (actual != nullptr)
    {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    delete cabeza;
    cabeza = nullptr;
}

/**
 * @brief Rota el puntero 'cabeza' N posiciones.
 * @param N Número de rotaciones (positivo=adelante, negativo=atrás).
 */
void RotorDeMapeo::rotar(int N)
{
    if (cabeza == nullptr || N == 0) return;

    int pasos = std::abs(N) % 27; 

    for (int i = 0; i < pasos; ++i)
    {
        if (N > 0)
        {
            cabeza = cabeza->siguiente; // Mover cabeza a la derecha (rotación positiva)
        }
        else
        {
            cabeza = cabeza->previo; // Mover cabeza a la izquierda (rotación negativa)
        }
    }
}

/**
 * @brief Decodifica un carácter de entrada según la rotación actual.
 * @param in El carácter codificado.
 * @return El carácter decodificado.
 */
char RotorDeMapeo::getMapeo(char in)
{
    // 1. Calcular la rotación actual (R): Pasos desde 'A' hasta la 'cabeza' actual.
    Nodo* puntero_A = cabeza;
    int rotacion_actual = 0;
    
    // Contar los pasos necesarios para llegar desde la 'cabeza' al carácter 'A' (o ' ').
    do {
        if (puntero_A->dato == 'A' || puntero_A->dato == ' ') break;
        puntero_A = puntero_A->siguiente; 
        rotacion_actual++; 
    } while (puntero_A != cabeza);
    
    // 2. Encontrar el carácter de entrada 'in' (X).
    Nodo* puntero_in = cabeza;
    do 
    {
        if (puntero_in->dato == in) 
        {
            break; 
        }
        puntero_in = puntero_in->siguiente;
    } while (puntero_in != cabeza);

    if (puntero_in->dato != in) {
        return in; // No se encuentra en el rotor
    }

    // 3. Decodificación: El carácter decodificado es el que está 'rotacion_actual' pasos DESPUÉS del caracter recibido 'in'.
    // Esto compensa la rotación de la Rueda de César.
    
    Nodo* resultado = puntero_in;
    for (int i = 0; i < rotacion_actual; ++i)
    {
        resultado = resultado->siguiente; // Mover hacia adelante (compensar la rotación)
    }
    
    return resultado->dato;
}