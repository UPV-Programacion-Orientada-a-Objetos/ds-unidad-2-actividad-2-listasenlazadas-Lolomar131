#include "SerialPort.h"
#include <cstdio>
#include <cstring>
#include <cerrno>

using namespace std;

// Función para configurar atributos (9600 baudios, 8N1)
int SerialPort::set_interface_attribs(int speed)
{
    struct termios tty;
    if (tcgetattr(fd, &tty) < 0) {
        perror("Error de tcgetattr");
        return -1;
    }

    // --- Configuración de Velocidad (Baud Rate) ---
    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    // --- Modo Local (Control Flags) ---
    tty.c_cflag |= (CLOCAL | CREAD);    // Habilitar receptor y modo local
    tty.c_cflag &= ~CSIZE;              // Enmascarar bits de tamaño de carácter
    tty.c_cflag |= CS8;                 // 8 bits de datos (8N1)
    tty.c_cflag &= ~PARENB;             // Sin paridad
    tty.c_cflag &= ~CSTOPB;             // 1 bit de parada

    // --- Modo de Entrada (Input Flags) ---
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
    tty.c_iflag &= ~IXON; // Deshabilitar control de flujo de software XON/XOFF

    // --- Modo de Salida (Output Flags) ---
    tty.c_oflag &= ~OPOST; // Deshabilitar post-procesamiento (salida sin procesar)
    tty.c_oflag &= ~ONLCR; // Deshabilitar mapeo NL -> CR-NL

    // --- Modo Local (Local Flags) ---
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN); // Entrada sin procesar (RAW mode)

    // --- Control de Caracteres (VMIN/VTIME) ---
    // VMIN = 0, VTIME = 1: lectura no bloqueante con timeout de 0.1 segundos.
    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 1;

    // Aplicar la configuración
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error de tcsetattr");
        return -1;
    }
    return 0;
}

SerialPort::SerialPort(const char* portname) : fd(-1)
{
    // O_RDWR: Abrir para lectura/escritura
    // O_NOCTTY: No hacer que sea el terminal de control
    // O_SYNC: Escrituras sincronizadas
    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    
    if (fd < 0)
    {
        fprintf(stderr, "Error al abrir el puerto serial %s: %s\n", portname, strerror(errno));
        return;
    }
    
    printf("Conexión establecida en %s. Configurando 9600 baudios...\n", portname);

    // Configurar 9600 baudios, 8 bits de datos, sin paridad, 1 bit de parada (8N1)
    if (set_interface_attribs(B9600) < 0)
    {
        close(fd);
        fd = -1;
        fprintf(stderr, "Error al configurar atributos del puerto.\n");
    }
    
    // Vaciar buffers de entrada para empezar limpio
    tcflush(fd, TCIOFLUSH);
}

SerialPort::~SerialPort()
{
    if (fd >= 0)
    {
        close(fd);
        printf("Puerto serial cerrado.\n");
    }
}

char* SerialPort::readLine()
{
    if (fd < 0) return nullptr;

    static char line_buffer[MAX_LINE_LENGTH]; // Buffer estático para la línea
    static int line_pos = 0;                  // Posición actual dentro del line_buffer
    char read_char;
    ssize_t n;

    while ((n = read(fd, &read_char, 1)) > 0)
    {
        if (line_pos >= MAX_LINE_LENGTH - 1)
        {
            // Error: línea demasiado larga. Resetear.
            line_pos = 0; 
            continue;
        }

        if (read_char == '\n' || read_char == '\r') // Fin de línea
        {
            if (line_pos > 0) // Si ya tenemos datos
            {
                line_buffer[line_pos] = '\0'; // Terminador de cadena C
                line_pos = 0; // Resetear para la próxima línea
                return line_buffer; // Devolver la línea completa
            }
            // Si solo es un \r o \n sin datos, ignorar y seguir leyendo.
            continue; 
        }

        // Agregar el carácter al buffer
        line_buffer[line_pos++] = read_char;
    }

    if (n < 0 && errno != EAGAIN) // Error real de lectura (no solo timeout)
    {
        perror("Error al leer el puerto serial");
    }
    
    return nullptr; // No se leyó una línea completa en este intento (timeout)
}