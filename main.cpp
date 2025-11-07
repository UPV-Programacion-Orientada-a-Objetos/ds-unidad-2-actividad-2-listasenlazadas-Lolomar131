#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include "TramaBase.h"
#include "SerialPort.h" 
#include <cstdio>      // Para printf
#include <cstring>     // Para strtok, strdup
#include <cstdlib>     // Para atoi, free
#include <unistd.h>    // Para usleep

// Define el puerto correcto de tu Arduino. ¡AJUSTA ESTO SI ES NECESARIO!
#define ARDUINO_PORT "/dev/ttyACM0" 

// Declaración de la función de parseo
TramaBase* parsear_linea(char* linea);

int main()
{
    // 1. Inicialización de estructuras
    ListaDeCarga miListaDeCarga;
    RotorDeMapeo miRotorDeMapeo;

    // 2. Inicialización del puerto serial real
    SerialPort miSerial(ARDUINO_PORT); 
    
    // Verificamos si la conexión fue exitosa
    if (!miSerial.is_open()) { 
        fprintf(stderr, "No se pudo iniciar el decodificador PRT-7 sin conexión serial.\n");
        return 1;
    }
    
    printf("Iniciando Decodificador PRT-7. Esperando tramas...\n\n");

    int tramas_procesadas = 0;
    int timeouts_consecutivos = 0;   // NUEVO: Contador de lecturas nulas
    const int MAX_TIMEOUTS = 5;      // NUEVO: Límite para asumir el fin del flujo
    const int TRAMAS_ESPERADAS = 12; // Cantidad de tramas que envía el Arduino

    // Bucle de Procesamiento: Intentará leer hasta 20 veces o hasta que detecte el fin del flujo
    while (tramas_procesadas < 20) 
    {
        char* trama_recibida_char = miSerial.readLine();

        if (trama_recibida_char != nullptr)
        {
            // Trama recibida con éxito
            timeouts_consecutivos = 0; // Resetear el contador de espera

            // Usamos strdup para obtener una copia mutable antes de usar strtok
            char* linea_mutable = strdup(trama_recibida_char);
            
            // 3. Parsear e Instanciar (Polimorfismo)
            TramaBase* trama = parsear_linea(linea_mutable);

            if (trama != nullptr)
            {
                // 4. Ejecutar y Limpiar
                trama->procesar(&miListaDeCarga, &miRotorDeMapeo);
                delete trama; 
                tramas_procesadas++;
            }
            // 5. Liberar la copia temporal
            free(linea_mutable);

        } else {
            // No se recibió una línea completa (timeout).
            timeouts_consecutivos++; 
            usleep(100000); // Esperar 100ms antes del siguiente intento

            // Lógica de SALIDA LIMPIA: Si ya procesamos las tramas esperadas 
            // y hemos tenido varios timeouts consecutivos, asumimos que el flujo terminó.
            if (timeouts_consecutivos >= MAX_TIMEOUTS && tramas_procesadas >= TRAMAS_ESPERADAS) {
                break; 
            }
        }
    }

    // 6. Resultado Final
    printf("\n---\nFlujo de datos terminado (leídas %d tramas).\n", tramas_procesadas);
    miListaDeCarga.imprimirMensaje();
    printf("---\nLiberando memoria... Sistema apagado.\n");
    
    // Los destructores de miListaDeCarga, miRotorDeMapeo y miSerial se llaman automáticamente aquí
    return 0;
}

/**
 * @brief Parsea la línea de texto recibida para instanciar la Trama correcta.
 * @param linea Cadena de caracteres C-style (char*) mutable.
 * @return Puntero a la TramaBase instanciada (TramaLoad* o TramaMap*), o nullptr si falla.
 */
TramaBase* parsear_linea(char* linea)
{
    char* tipo_str = strtok(linea, ",");
    char* valor_str = strtok(nullptr, ",");

    if (tipo_str == nullptr || valor_str == nullptr) return nullptr;

    char tipo = *tipo_str;

    if (tipo == 'L')
    {
        char fragmento = *valor_str;
        return new TramaLoad(fragmento);
    }
    else if (tipo == 'M')
    {
        int N = atoi(valor_str);
        return new TramaMap(N);
    }
    
    return nullptr;
}