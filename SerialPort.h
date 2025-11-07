#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <unistd.h>  
#include <fcntl.h>   
#include <termios.h> 

#define MAX_LINE_LENGTH 128 

/**
 * @class SerialPort
 * @brief Clase para manejar la conexión y lectura desde el puerto serial en Linux.
 * * Abstrae las complejidades de la API POSIX (termios).
 */
class SerialPort
{
private:
    int fd; ///< File Descriptor (identificador) del puerto serial. Es -1 si la conexión falla.
    char read_buffer[MAX_LINE_LENGTH]; 

    /**
     * @brief Configura la velocidad (9600), paridad (8N1) y modos de lectura.
     */
    int set_interface_attribs(int speed);

public:
    /**
     * @brief Constructor. Abre y configura el puerto serial.
     * @param portname El nombre del dispositivo (ej. "/dev/ttyACM0").
     */
    SerialPort(const char* portname);

    /**
     * @brief Destructor. Cierra el puerto serial.
     */
    ~SerialPort();

    /**
     * @brief Verifica si el puerto serial se abrió con éxito.
     * @return true si la conexión está lista.
     */
    bool is_open() const { return fd >= 0; }

    /**
     * @brief Lee una línea completa (hasta \n o \r) del puerto.
     * @return Puntero a la cadena leída (char*), o nullptr si hay timeout.
     */
    char* readLine();
};

#endif // SERIALPORT_H