#ifndef UDEASTAY_H
#define UDEASTAY_H

#include "Anfitrion.h"
#include "Huesped.h"
#include "Alojamiento.h"
#include "Reserva.h"
#include "Fecha.h"

class UdeAStay {
private:
    // Listas principales
    Anfitrion** listaAnfitriones;
    Huesped** listaHuespedes;
    Alojamiento** listaAlojamientos;
    Reserva** listaReservasVigentes;
    Reserva** listaReservasHistoricas;

    // Fecha límite actual para reservas (1 año desde hoy)
    Fecha fechaCorte;

    // Cantidades y capacidades
    int cantidadAnfitriones, capacidadAnfitriones;
    int cantidadHuespedes, capacidadHuespedes;
    int cantidadAlojamientos, capacidadAlojamientos;
    int cantidadReservasVigentes, capacidadReservasVigentes;
    int cantidadReservasHistoricas, capacidadReservasHistoricas;

    // Estadísticas de recursos
    long totalIteraciones;
    long totalMemoria;

    // Métodos internos de apoyo
    void redimensionarAnfitriones();
    void redimensionarHuespedes();
    void redimensionarAlojamientos();
    void redimensionarReservasVigentes();
    void redimensionarReservasHistoricas();

    Huesped* buscarHuespedPorDocumento(const char* documento);
    Anfitrion* buscarAnfitrionPorDocumento(const char* documento);
    Alojamiento* buscarAlojamientoPorCodigo(const char* codigo);

    bool validarDisponibilidad(Alojamiento* a, Fecha inicio, int duracion);

public:
    // Constructor y destructor
    UdeAStay();
    ~UdeAStay();

    // Funcionalidad I - Carga de datos
    void cargarDatosDesdeArchivo();     // Carga todo desde txts
    void guardarDatosEnArchivo();       // Guarda todas las entidades

    // Funcionalidad II - Iniciar sesión
    void iniciarSesion(const char* documentoIdentidad, int tipoUsuario);

    // Funcionalidad III - Crear reserva
    void crearReserva(const char* documentoHuesped, const char* codigoAlojamiento,
                      Fecha fechaEntrada, int duracion, int metodoPago,
                      const Fecha& fechaPago, double monto, const char* anotaciones);

    // Funcionalidad IV - Anular reserva
    void anularReserva(const char* codigoReserva);

    // Funcionalidad V - Consultar reservas por anfitrión
    void consultarReservasAnfitrion(const char* documentoAnfitrion,
                                    const Fecha& desde,
                                    const Fecha& hasta);

    // Funcionalidad VI - Actualizar histórico
    void actualizarHistorico(const Fecha& nuevaFechaCorte);

    // Funcionalidad VII - Estadísticas del sistema
    void medirConsumoDeRecursos();

    // Funcionalidades auxiliares (para lógica interna)
    int buscarHuespedIndex(const char* documento);
    int buscarAlojamientoIndex(const char* codigo);
    Reserva* buscarReserva(const char* codigo);
};

#endif // UDEASTAY_H
