#ifndef TRAMABASE_H
#define TRAMABASE_H

#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @class TramaBase
 * @brief Clase Base Abstracta (ABC) para todas las tramas (L/M).
 * * Define la interfaz polimórfica para el procesamiento de tramas.
 */
class TramaBase
{
public:
    /**
     * @brief Destructor Virtual. Es OBLIGATORIO para limpiar correctamente 
     * la memoria de las clases derivadas al usar un puntero TramaBase*.
     */
    virtual ~TramaBase() {}

    /**
     * @brief Método Virtual Puro. Define la acción que la trama debe realizar.
     * @param carga Puntero a la ListaDeCarga.
     * @param rotor Puntero al RotorDeMapeo.
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};


/**
 * @class TramaLoad
 * @brief Representa una Trama de Carga (L, X). Contiene un fragmento de dato.
 */
class TramaLoad : public TramaBase
{
private:
    char fragmento; ///< El carácter a decodificar.
public:
    TramaLoad(char f);
    virtual ~TramaLoad() override;
    
    /**
     * @brief Decodifica el fragmento usando el rotor y lo añade a la lista de carga.
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

/**
 * @class TramaMap
 * @brief Representa una Trama de Mapeo (M, N). Contiene la instrucción de rotación.
 */
class TramaMap : public TramaBase
{
private:
    int N; ///< Valor de la rotación (positivo o negativo).
public:
    TramaMap(int n);
    virtual ~TramaMap() override;
    
    /**
     * @brief Ejecuta la rotación del rotor.
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMABASE_H