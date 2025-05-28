#ifndef UDEASTAY_H
#define UDEASTAY_H

#include "Anfitrion.h"
#include "Huesped.h"
#include "Alojamiento.h"
#include "Reserva.h"
#include "Fecha.h"

// Clase principal que administra el sistema UdeAStay.
// Se encarga de gestionar los datos y operaciones del sistema:
// - Carga y guardado automático de datos en archivos
// - Gestión de reservas y fechas de corte
// - Inicio de sesión de usuarios
// - Consultas por anfitrión
// - Métricas de consumo del sistema

class UdeAStay {
private:
    // SECCIÓN 1: ESTRUCTURAS INTERNAS

    // Listas principales de punteros dinámicos
    Anfitrion** listaAnfitriones;
    Huesped** listaHuespedes;
    Alojamiento** listaAlojamientos;
    Reserva** listaReservasVigentes;
    Reserva** listaReservasHistoricas;

    // Fecha que representa el corte actual del sistema
    Fecha fechaCorte;

    // Cantidad y capacidad de cada lista dinámica
    int cantidadAnfitriones, capacidadAnfitriones;
    int cantidadHuespedes, capacidadHuespedes;
    int cantidadAlojamientos, capacidadAlojamientos;
    int cantidadReservasVigentes, capacidadReservasVigentes;
    int cantidadReservasHistoricas, capacidadReservasHistoricas;

    //Usuario actuaalmente en sesion
    Anfitrion* anfitrionActivo;
    Huesped* huespedActivo;

    // Métricas de consumo de recursos
    long totalIteraciones;
    long totalMemoria;
    int archivosAbiertos;
    int lineasLeidas;

    // Constantes para tipo de usuario y método de pago
    enum TipoUsuario { TIPO_ANFITRION = 2, TIPO_HUESPED = 1 };
    enum MetodoPago { METODO_PSE = 0, METODO_TARJETA_CREDITO = 1 };

    // SECCIÓN 2: REDIMENSIONAMIENTO

    void redimensionarAnfitriones();
    void redimensionarHuespedes();
    void redimensionarAlojamientos();
    void redimensionarReservasVigentes();
    void redimensionarReservasHistoricas();

    // SECCIÓN 3: FUNCIONES DE BÚSQUEDA

    Huesped* buscarHuespedPorDocumento(const char* documento);
    Anfitrion* buscarAnfitrionPorDocumento(const char* documento);
    Alojamiento* buscarAlojamientoPorCodigo(const char* codigo);

    int buscarHuespedIndex(const char* documento);
    int buscarAlojamientoIndex(const char* codigo);
    Reserva* buscarReserva(const char* codigo);


    // SECCIÓN 4: MANEJO DE TEXTO

    // Funciones de texto reutilizadas desde Funciones.h

    // SECCIÓN 5: FUNCIONES AUXILIARES

    bool validarDisponibilidad(Alojamiento* a, const Fecha& inicio, int duracion);
    Fecha leerFechaMasRecienteDelHistorico(const char* ruta);
    bool esFechaPosterior(const Fecha& nuevaFecha, const Fecha& fechaExistente);

    char* extraerCampo(const char* linea, int indice);
    int contarCampos(const char* linea);
    void dividirAmenidades(Alojamiento* alojamiento, const char* texto);

    // SECCIÓN 6: MANEJO DE ARCHIVOS

    // Carga desde archivos .txt (ubicados en ../datos/)
    void cargarAnfitriones(const char* ruta);
    void cargarHuespedes(const char* ruta);
    void cargarAlojamientos(const char* ruta);
    void cargarReservasVigentes(const char* ruta);
    void cargarReservasHistoricas(const char* ruta);
    void cargarFechaCorte(const char* ruta);

    // Guardado en archivos .txt
    void guardarAnfitriones(const char* ruta);
    void guardarHuespedes(const char* ruta);
    void guardarAlojamientos(const char* ruta);
    void guardarReservasVigentes(const char* ruta);
    void guardarReservasHistoricas(const char* ruta);
    void guardarFechaCorte(const char* ruta, const Fecha& fecha);

    // Conversión de texto numérico sin atoi/atof
    int convertirEntero(const char* texto);
    double convertirDouble(const char* texto);

    // Utilidad para reservas
    char* generarCodigoReserva();
    void crearReservaDesdeTexto(const char* linea);

public:
    // SECCIÓN 7: CONSTRUCTOR Y DESTRUCTOR

    UdeAStay();
    ~UdeAStay();

    // SECCIÓN 8: FUNCIONALIDADES PRINCIPALES

    // Muestra alojamientos disponibles según filtros (para huésped)
    void buscarAlojamientos(const Fecha& fechaInicio,
                            int duracion,
                            const char* municipio,
                            double precioMaximo = -1,
                            float puntuacionMinima = -1,
                            const char* codigo = nullptr);
    // Carga todos los archivos base del sistema al iniciar
    void cargarDatosDesdeArchivos();

    // Guarda todos los datos modificados en sus archivos respectivos
    void guardarDatosEnArchivos();

    //Inicia sesión y fija el usuario activo según el documento y rol.
    //return true si se encontró y estableció el usuario activo.
    bool iniciarSesion(const char* documento, int tipoUsuario);

    // Cierra la sesión actual (reset de usuario activo)
    void cerrarSesion();

    // Crea una nueva reserva a partir de datos provistos por un huésped
    void crearReserva(const char* documentoHuesped,
                      const char* codigoAlojamiento,
                      const Fecha& fechaEntrada,
                      int duracion,
                      int metodoPago,
                      const Fecha& fechaPago,
                      double monto,
                      const char* anotaciones);

    // Anula una reserva activa con base en su código
    void anularReserva(const char* codigoReserva);

    // Consulta las reservas asociadas a un anfitrión en un rango de fechas
    void consultarReservasAnfitrion(const char* documentoAnfitrion,
                                    const Fecha& desde,
                                    const Fecha& hasta);

    // Mueve las reservas anteriores a la nueva fecha de corte al histórico
    void actualizarHistorico(const Fecha& nuevaFechaCorte);

    // Mide el consumo interno de recursos del sistema
    void medirConsumoDeRecursos();

    // Muestra un resumen general del estado actual del sistema
    void mostrarResumenDatos() const;

    //Pa ver las reservas de un huesped
    void mostrarReservasHuespedActivo() const;

    // Getters para obtener métricas actuales del sistema
    int getCantidadHuespedes() const;
    int getCantidadAnfitriones() const;
    int getCantidadAlojamientos() const;
    int getCantidadReservasVigentes() const;
    int getCantidadReservasHistoricas() const;

    Huesped* getHuespedActivo() const { return huespedActivo; }
    Anfitrion* getAnfitrionActivo() const { return anfitrionActivo; }

};

#endif // UDEASTAY_H
