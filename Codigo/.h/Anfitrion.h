#ifndef ANFITRION_H
#define ANFITRION_H

#include "Fecha.h"
class Alojamiento;  // Solo usamos puntero

// Esta clase representa a un anfitrión dentro del sistema.
// Cada anfitrión tiene un documento, nombre, puntuación y aloja alojamientos (valga la redundancia).
class Anfitrion {
private:
    char* documentoIdentidad;         // ID único del anfitrión
    char* nombreCompleto;             // Su nombre completo
    int antiguedadEnMeses;            // Cuánto lleva en la plataforma
    float puntuacion;                 // Su calificación

    // Como puede tener varios alojamientos, usamos un arreglo dinámico de punteros
    Alojamiento** listaAlojamientos;
    int cantidadAlojamientos;
    int capacidadAlojamientos;

    // Cosas internas para copiar texto y aumentar tamaño si se llena el arreglo
    char* copiarTexto(const char* texto) const;
    void redimensionarAlojamientos();

public:
    // Constructor principal
    Anfitrion(const char* documento, const char* nombre, int antiguedad);

    // Para copiar anfitriones si toca (aunque no lo usamos mucho, por si acaso)
    Anfitrion(const Anfitrion& otro);

    // Destructor (liberamos memoria dinámica)
    ~Anfitrion();

    // Métodos para consultar cosas básicas
    char* getDocumentoIdentidad() const;
    char* getNombreCompleto() const;
    int getAntiguedadEnMeses() const;
    float getPuntuacion() const;
    int getCantidadAlojamientos() const;

    // Para cambiar su nombre o puntuación si se requiere
    void setNombreCompleto(const char* nombre);
    void setPuntuacion(float puntuacion);

    // Agrega un alojamiento nuevo al arreglo
    void agregarAlojamiento(Alojamiento* alojamiento);

    // Muestra todas las reservas de sus alojamientos entre dos fechas
    void verReservaciones(const Fecha& desde, const Fecha& hasta) const;

    // Le pide a sus alojamientos que anulen alguna reserva
    void anularReservacion(const char* codigoReserva);
};

#endif // ANFITRION_H
