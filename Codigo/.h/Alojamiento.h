#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include "Fecha.h"
class Anfitrion;

// Esta clase representa un alojamiento ofrecido por un anfitrión.
// Contiene la información necesaria para identificarlo, calcular disponibilidad,
// gestionar reservas, mostrar amenidades, y saber quién es su dueño.
class Alojamiento {
private:
    // Datos básicos del alojamiento
    char* codigo;         // Código único del alojamiento
    char* nombre;         // Nombre comercial (ej. "Casa en el lago")
    char* departamento;   // Departamento donde se encuentra
    char* municipio;      // Municipio
    char* direccion;      // Dirección específica
    int tipoAlojamiento;  // 0 = casa, 1 = apartamento
    double precioPorNoche;

    // Amenidades como bits (ej. 1 = wifi, 2 = piscina, etc.)
    int amenidades;

    // Listas dinámicas de reservas
    Fecha* fechasInicioReservadas;  // Arreglo de fechas de entrada
    int* duracionesReservadas;      // Duraciones de cada reserva en noches
    int cantidadReservaciones;      // Cuántas reservas hay actualmente
    int capacidadReservaciones;     // Capacidad máxima antes de redimensionar

    // Dueño del alojamiento (apunta al anfitrión)
    Anfitrion* dueno;

    // Métodos internos útiles
    char* copiarTexto(const char* texto) const; // Copia segura de texto dinámico
    void redimensionarReservas();               // Duplica la capacidad si se llena el arreglo

public:
    // Constructor principal para crear el alojamiento desde cero
    Alojamiento(const char* cod, const char* nom, const char* dep, const char* mun,
                const char* dir, int tipo, double precio, Anfitrion* dueno);

    // Constructor de copia (por si hay que duplicar uno existente)
    Alojamiento(const Alojamiento& otro);

    // Destructor (libera toda la memoria dinámica)
    ~Alojamiento();

    // Métodos para consultar los datos del alojamiento
    char* getCodigo() const;
    char* getNombre() const;
    char* getDepartamento() const;
    char* getMunicipio() const;
    char* getDireccion() const;
    int getTipoAlojamiento() const;
    double getPrecioPorNoche() const;
    int getAmenidades() const;

    // Métodos para trabajar con amenidades específicas
    bool tieneAmenidad(int amenidad) const;
    void agregarAmenidad(int amenidad);
    void quitarAmenidad(int amenidad);
    void mostrarAmenidades() const;

    // Verifica si el alojamiento está libre en una fecha exacta
    bool estaDisponible(const Fecha& inicio) const;

    // Registra una nueva reserva con fecha y duración
    void agregarReservacion(const Fecha& inicio, int duracion);

    // Elimina una reserva (a futuro, por ahora es simulado)
    void eliminarReservacion(const char* codigoReserva);

    // Muestra todas las reservas que estén entre dos fechas
    void mostrarReservasEnRango(const Fecha& desde, const Fecha& hasta) const;

    // Devuelve el puntero al anfitrión que es dueño de este alojamiento
    Anfitrion* getAnfitrionResponsable() const;
};

#endif // ALOJAMIENTO_H
