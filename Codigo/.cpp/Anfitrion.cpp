#include "Anfitrion.h"
#include "Alojamiento.h"
#include "Funciones.h"  // Usamos las funciones globales: copiarTexto, sonIguales, etc.

// Inicialización de variables estáticas
int Anfitrion::contadorAnfitriones = 0;
int Anfitrion::totalAnfitrionesCreados = 0;
int Anfitrion::totalIteracionesEnAlojamientos = 0;

// Constructor principal (genera código tipo ANF001 automáticamente)
Anfitrion::Anfitrion(const char* nombre, int antiguedad) {
    antiguedadEnMeses = antiguedad;
    puntuacion = 5.0f; // Valor inicial por defecto

    // Generar documento/código automáticamente
    contadorAnfitriones++;
    totalAnfitrionesCreados++;

    char codigoGenerado[10];
    codigoGenerado[0] = 'A';
    codigoGenerado[1] = 'N';
    codigoGenerado[2] = 'F';
    codigoGenerado[3] = (contadorAnfitriones / 100) % 10 + '0';
    codigoGenerado[4] = (contadorAnfitriones / 10) % 10 + '0';
    codigoGenerado[5] = contadorAnfitriones % 10 + '0';
    codigoGenerado[6] = '\0';

    documentoIdentidad = copiarTexto(codigoGenerado);
    nombreCompleto = copiarTexto(nombre);

    capacidadAlojamientos = 5;
    cantidadAlojamientos = 0;
    listaAlojamientos = new Alojamiento*[capacidadAlojamientos];
}

// Constructor de copia
Anfitrion::Anfitrion(const Anfitrion& otro) {
    documentoIdentidad = copiarTexto(otro.documentoIdentidad);
    nombreCompleto = copiarTexto(otro.nombreCompleto);
    antiguedadEnMeses = otro.antiguedadEnMeses;
    puntuacion = otro.puntuacion;

    capacidadAlojamientos = otro.capacidadAlojamientos;
    cantidadAlojamientos = otro.cantidadAlojamientos;
    listaAlojamientos = new Alojamiento*[capacidadAlojamientos];

    for (int i = 0; i < cantidadAlojamientos; i++) {
        listaAlojamientos[i] = otro.listaAlojamientos[i]; // Copia superficial
    }

    totalAnfitrionesCreados++;
}

// Destructor
Anfitrion::~Anfitrion() {
    delete[] documentoIdentidad;
    delete[] nombreCompleto;
    delete[] listaAlojamientos;
}

// Getters
char* Anfitrion::getDocumentoIdentidad() const {
    return copiarTexto(documentoIdentidad);
}

char* Anfitrion::getNombreCompleto() const {
    return copiarTexto(nombreCompleto);
}

int Anfitrion::getAntiguedadEnMeses() const {
    return antiguedadEnMeses;
}

float Anfitrion::getPuntuacion() const {
    return puntuacion;
}

int Anfitrion::getCantidadAlojamientos() const {
    return cantidadAlojamientos;
}

// Setters
void Anfitrion::setNombreCompleto(const char* nombre) {
    delete[] nombreCompleto;
    nombreCompleto = copiarTexto(nombre);
}

void Anfitrion::setPuntuacion(float nuevaPuntuacion) {
    puntuacion = nuevaPuntuacion;
}

void Anfitrion::setDocumentoIdentidad(const char* documento) {
    delete[] documentoIdentidad;
    documentoIdentidad = copiarTexto(documento);
}

// Redimensionar alojamientos
void Anfitrion::redimensionarAlojamientos() {
    int nuevaCapacidad = capacidadAlojamientos * 2;
    Alojamiento** nuevoArreglo = new Alojamiento*[nuevaCapacidad];

    for (int i = 0; i < cantidadAlojamientos; i++) {
        nuevoArreglo[i] = listaAlojamientos[i];
    }

    delete[] listaAlojamientos;
    listaAlojamientos = nuevoArreglo;
    capacidadAlojamientos = nuevaCapacidad;
}

// Agrega un nuevo alojamiento
void Anfitrion::agregarAlojamiento(Alojamiento* alojamiento) {
    if (cantidadAlojamientos == capacidadAlojamientos) {
        redimensionarAlojamientos();
    }
    listaAlojamientos[cantidadAlojamientos++] = alojamiento;
}

// Ver reservas en un rango
void Anfitrion::verReservaciones(const Fecha& desde, const Fecha& hasta) const {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        totalIteracionesEnAlojamientos++;
        listaAlojamientos[i]->mostrarReservasEnRango(desde, hasta);
    }
}

// Anular reserva en todos sus alojamientos
void Anfitrion::anularReservacion(const Fecha& inicio, int duracion) {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        totalIteracionesEnAlojamientos++;
        listaAlojamientos[i]->eliminarReservacion(inicio, duracion);
    }
}

// Reporte de uso de recursos
int Anfitrion::getTotalAnfitrionesCreados() {
    return totalAnfitrionesCreados;
}

int Anfitrion::getTotalIteraciones() {
    return totalIteracionesEnAlojamientos;
}
