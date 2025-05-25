#ifndef UDEASTAY_H
#define UDEASTAY_H

#include "Anfitrion.h"
#include "Huesped.h"
#include "Alojamiento.h"
#include "Reserva.h"
#include "Fecha.h"

// Clase principal que administra el sistema UdeAStay.
// Se encarga de gestionar los datos y operaciones del sistema:
// - Carga de archivos
// - Gestión de reservas
// - Inicio de sesión
// - Consultas por anfitrión
// - Métricas de consumo
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

    // Métricas de consumo de recursos
    long totalIteraciones;
    long totalMemoria;
    int archivosAbiertos;
    int lineasLeidas;

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

    int buscarHuespedIndex(const char* documento);     // Para pruebas o referencias cruzadas
    int buscarAlojamientoIndex(const char* codigo);
    Reserva* buscarReserva(const char* codigo);

    // SECCIÓN 4: MANEJO DE TEXTO

    char* copiarTexto(const char* fuente);
    bool sonIguales(const char* a, const char* b);
    bool iniciaCon(const char* texto, const char* prefijo);

    // SECCIÓN 5: FUNCIONES AUXILIARES

    bool validarDisponibilidad(Alojamiento* a, const Fecha& inicio, int duracion);

    char* extraerCampo(const char* linea, int indice);
    int contarCampos(const char* linea);
    void dividirAmenidades(Alojamiento* alojamiento, const char* texto);

    // SECCIÓN 6: MANEJO DE ARCHIVOS

    // Carga desde archivos .txt
    void cargarAnfitrionesDesdeArchivo(const char* ruta);
    void cargarHuespedesDesdeArchivo(const char* ruta);
    void cargarAlojamientosDesdeArchivo(const char* ruta);
    void cargarReservasDesdeArchivo(const char* ruta);

    // Guardado en archivos .txt (puedes completar luego)
    void guardarAnfitrionesEnArchivo(const char* ruta);
    void guardarHuespedesEnArchivo(const char* ruta);
    void guardarAlojamientosEnArchivo(const char* ruta);
    void guardarReservasEnArchivo(const char* ruta);

    // Persistencia de la fecha de corte
    Fecha leerFechaArchivo(const char* nombreArchivo);
    void guardarFechaArchivo(const char* nombreArchivo, const Fecha& fecha);

    // Funciones auxiliares para conversión de texto numérico
    // Para convertir texto numérico a entero (sin usar atoi)
    int convertirEntero(const char* texto);
    // Para convertir texto numérico a double (sin usar atof)
    double convertirDouble(const char* texto);

    // Carga desde archivo histórico adicional
    void cargarReservasHistoricasDesdeArchivo(const char* ruta);

    // Guardado de reservas en archivos separados
    void guardarReservasVigentesEnArchivo(const char* ruta);
    void guardarReservasHistoricasEnArchivo(const char* ruta);

public:
    // SECCIÓN 7: CONSTRUCTOR Y DESTRUCTOR

    UdeAStay();
    ~UdeAStay();

    // SECCIÓN 8: FUNCIONALIDADES PRINCIPALES

    // Funcionalidad I – Carga y guardado de datos
    void cargarDatosDesdeArchivo();
    void guardarDatosEnArchivo();

    // Funcionalidad II – Iniciar sesión por documento
    void iniciarSesion(const char* documentoIdentidad, int tipoUsuario);

    // Funcionalidad III – Crear nueva reserva
    void crearReserva(const char* documentoHuesped,
                      const char* codigoAlojamiento,
                      const Fecha& fechaEntrada,
                      int duracion,
                      int metodoPago,
                      const Fecha& fechaPago,
                      double monto,
                      const char* anotaciones);

    // Funcionalidad IV – Anular reserva por código
    void anularReserva(const char* codigoReserva);

    // Funcionalidad V – Consultar reservas del anfitrión en un rango
    void consultarReservasAnfitrion(const char* documentoAnfitrion,const Fecha& desde,const Fecha& hasta);

    // Funcionalidad VI – Actualizar histórico con nueva fecha de corte
    void actualizarHistorico(const Fecha& nuevaFechaCorte);

    // Funcionalidad VII – Medir consumo de recursos
    void medirConsumoDeRecursos();

    // Funcionalidad auxiliar – Mostrar estado general
    void mostrarResumenDatos() const;

    // Getters de cantidad de elementos
    int getCantidadHuespedes() const;
    int getCantidadAnfitriones() const;
    int getCantidadAlojamientos() const;
    int getCantidadReservasVigentes() const;
    int getCantidadReservasHistoricas() const;
};

#endif // UDEASTAY_H
