#ifndef SERIALSIM_H
#define SERIALSIM_H

/**
 * @brief Implementación para SIMULAR la lectura de tramas seriales.
 * Evita la complejidad de las APIs de puerto COM (Win32/termios) para la prueba inicial.
 */
class SerialSim
{
private:
    int indice_trama_actual;
    // La secuencia de prueba requerida por el caso de estudio
    const char* tramas[13] = {
        "L,H", "L,O", "L,L", "M,2", 
        "L,A", "L, ", "L,W", "M,-2",
        "L,O", "L,R", "L,L", "L,D",
        nullptr // Marcador de fin de flujo
    };

public:
    SerialSim();

    /**
     * @brief Simula la lectura de la siguiente línea del puerto serial.
     * @return Puntero a la cadena de caracteres C-style (char*) de la trama, o nullptr si terminó.
     */
    const char* leerSiguienteTrama();
};

#endif // SERIALSIM_H