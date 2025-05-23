#ifndef ANFITRION_H
#define ANFITRION_H

#include "Fecha.h"
class Alojamiento;  // Solo usamos puntero
// Esta clase representa a un anfitrión dentro del sistema.
// Cada anfitrión tiene un documento/código único que ahora se genera internamente.
// Usamos 'static' para que el contador sea compartido entre todos los objetos de la clase,
// Usamos 'const' para asegurar que ciertas funciones (como copiar texto o getters)
// no modifiquen el estado del objeto y sean más seguras y predecibles.
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

    // Cosas internas para manejo seguro
    char* copiarTexto(const char* texto) const;
    void redimensionarAlojamientos();// Esta función duplica el tamaño del arreglo de alojamientos cuando ya no hay más espacio.

    // Funciones auxiliares
    int longitudTexto(const char* texto) const;
    void copiarTexto(char* destino, const char* fuente) const;

    // Contador estático para generar códigos únicos tipo "ANF001"
    static int contadorAnfitriones;

    // Contadores de recursos
    static int totalAnfitrionesCreados;
    static int totalIteracionesEnAlojamientos;

public:
    // Constructor principal (ahora genera código automáticamente)
    Anfitrion(const char* nombre, int antiguedad);

    // Constructor de copia
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

    // Métodos para reportar uso de recursos
    static int getTotalAnfitrionesCreados();
    static int getTotalIteraciones();
};

#endif // ANFITRION_H
