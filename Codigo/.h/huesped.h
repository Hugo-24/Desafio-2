#ifndef HUESPED_H
#define HUESPED_H

#include "Fecha.h"
class Reserva;

// Clase que representa a un huésped que realiza reservas en el sistema.
class Huesped {
private:
    char* codigo;                 // Código autogenerado HSP-0001, HSP-0002, ...
    char* nombreCompleto;        // Nombre del huésped
    char* documentoIdentidad;    // Documento de identidad
    int antiguedadEnMeses;       // Antigüedad en la plataforma
    double puntuacionPromedio;   // Valor entre 0.0 y 5.0

    // Lista dinámica de reservas
    Reserva** listaReservas;
    int cantidadReservas;
    int capacidadReservas;

    // Funciones internas
    void redimensionarReservas();     // Duplica capacidad si se llena
    void generarCodigo();             // Generador tipo HSP-0001

    // Contadores estáticos
    static int siguienteId;
    static int totalHuespedesCreados;
    static int totalIteracionesEnReservas;

public:
    // Constructor principal
    Huesped(const char* nombre, const char* documento, int antiguedad, double puntuacion = 5.0);

    // Constructor de copia
    Huesped(const Huesped& otro);

    // Operador de asignación
    Huesped& operator=(const Huesped& otro);

    // Destructor
    ~Huesped();

    // Accesores
    const char* getCodigo() const;
    const char* getNombreCompleto() const;
    const char* getDocumentoIdentidad() const;
    int getAntiguedadEnMeses() const;
    double getPuntuacionPromedio() const;
    int getCantidadReservas() const;
    Reserva* getReserva(int indice) const;

    // Gestión de reservas
    void agregarReserva(Reserva* reserva);
    void anularReservacion(const Fecha& fecha, int duracion);
    void mostrarReservas() const;

    // Muestra resumen de info básica
    void imprimirResumen() const;

    // Estadísticas globales
    static int getTotalHuespedesCreados();
    static int getTotalIteraciones();
};

#endif // HUESPED_H
