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
    Huesped**   listaHuespedes;
    Alojamiento** listaAlojamientos;
    Reserva**   listaReservasVigentes;
    Reserva**   listaReservasHistoricas;

    // Fecha de la última ejecución y límite para histórico
    Fecha fechaCorte;

    // Cantidades y capacidades
    int cantidadAnfitriones, capacidadAnfitriones;
    int cantidadHuespedes,   capacidadHuespedes;
    int cantidadAlojamientos,capacidadAlojamientos;
    int cantidadReservasVigentes,   capacidadReservasVigentes;
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

    Huesped*   buscarHuespedPorDocumento(const char* documento);
    Anfitrion* buscarAnfitrionPorDocumento(const char* documento);
    Alojamiento*buscarAlojamientoPorCodigo(const char* codigo);

    bool validarDisponibilidad(Alojamiento* a, const Fecha& inicio, int duracion);

    // Manejo de fecha persistente
    Fecha leerFechaArchivo(const char* nombreArchivo);
    void  guardarFechaArchivo(const char* nombreArchivo, const Fecha& fecha);

public:
    // Constructor y destructor
    UdeAStay();
    ~UdeAStay();

    // Para pruebas en main()
    int getCantidadHuespedes() const;
    int getCantidadAnfitriones() const;
    int getCantidadAlojamientos() const;
    int getCantidadReservasVigentes() const;
    int getCantidadReservasHistoricas() const;

    void mostrarResumenDatos() const;

    // Funcionalidad I – Carga y guardado de datos
    void cargarDatosDesdeArchivo();
    void guardarDatosEnArchivo();

    // Funcionalidad II – Iniciar sesión (valida fecha y actualiza histórico)
    void iniciarSesion(const char* documentoIdentidad, int tipoUsuario);

    // III – Crear reserva
    void crearReserva(const char* documentoHuesped,
                      const char* codigoAlojamiento,
                      const Fecha& fechaEntrada,
                      int duracion,
                      int metodoPago,
                      const Fecha& fechaPago,
                      double monto,
                      const char* anotaciones);

    // IV – Anular reserva
    void anularReserva(const char* codigoReserva);

    // V – Consultar reservas de anfitrión
    void consultarReservasAnfitrion(const char* documentoAnfitrion,
                                    const Fecha& desde,
                                    const Fecha& hasta);

    // VI – Actualizar histórico manualmente
    void actualizarHistorico(const Fecha& nuevaFechaCorte);

    // VII – Medir consumo de recursos
    void medirConsumoDeRecursos();

    // Auxiliares de búsqueda (para menús y pruebas)
    int    buscarHuespedIndex(const char* documento);
    int    buscarAlojamientoIndex(const char* codigo);
    Reserva* buscarReserva(const char* codigo);
};

#endif // UDEASTAY_H
