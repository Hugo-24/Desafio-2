#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include "Fecha.h"
class Anfitrion;

// Esta clase representa un alojamiento ofrecido por un anfitrión.
// Contiene la información necesaria para identificarlo, calcular disponibilidad,
// gestionar reservas, mostrar amenidades, y saber quién es su dueño.
// Usamos memoria dinámica para todo (sin STL) y agregamos contadores para análisis de recursos.
class Alojamiento {
private:
    // Datos básicos del alojamiento
    char* codigo;
    char* nombre;
    char* departamento;
    char* municipio;
    char* direccion;
    int tipoAlojamiento;       // 0 = casa, 1 = apartamento
    double precioPorNoche;

    // Amenidades usando bits (bitmask)
    int amenidades;

    // Listas dinámicas de reservas
    Fecha* fechasInicioReservadas;
    int* duracionesReservadas;
    int cantidadReservaciones;
    int capacidadReservaciones;

    // Dueño del alojamiento
    Anfitrion* dueno;

    // Métodos internos
    void redimensionarReservas();  // Duplica capacidad si se llena el arreglo

    // Contadores estáticos para análisis de recursos
    static int totalAlojamientosCreados;
    static int totalIteracionesEnReservas;

public:
    // Constructor principal
    Alojamiento(const char* cod, const char* nom, const char* dep, const char* mun,
                const char* dir, int tipo, double precio, Anfitrion* dueno);

    // Constructor de copia
    Alojamiento(const Alojamiento& otro);

    // Destructor
    ~Alojamiento();

    // Getters básicos
    char* getCodigo() const;
    char* getNombre() const;
    char* getDepartamento() const;
    char* getMunicipio() const;
    char* getDireccion() const;
    int getTipoAlojamiento() const;
    double getPrecioPorNoche() const;
    int getAmenidades() const;

    // Métodos para amenidades
    bool tieneAmenidad(int amenidad) const;
    void agregarAmenidad(int amenidad);
    void quitarAmenidad(int amenidad);
    void mostrarAmenidades() const;

    // Gestión de reservas
    bool estaDisponible(const Fecha& inicio) const;
    void agregarReservacion(const Fecha& inicio, int duracion);
    void eliminarReservacion(const Fecha& inicio, int duracion);
    void mostrarReservasEnRango(const Fecha& desde, const Fecha& hasta) const;

    // Dueño del alojamiento
    Anfitrion* getAnfitrionResponsable() const;

    // Acceso a los contadores de recursos
    static int getTotalAlojamientosCreados();
    static int getTotalIteraciones();
};

#endif // ALOJAMIENTO_H
