#include "Anfitrion.h"
#include "Alojamiento.h"
#include <iostream>
#include <cstring>

using namespace std;

// Copia segura de texto dinámico
char* Anfitrion::copiarTexto(const char* texto) const {
    size_t longitud = strlen(texto);
    char* copia = new char[longitud + 1];
    strncpy(copia, texto, longitud);
    copia[longitud] = '\0';
    return copia;
}

// Constructor principal
Anfitrion::Anfitrion(const char* documento, const char* nombre, int antiguedad) {
    documentoIdentidad = copiarTexto(documento);
    nombreCompleto = copiarTexto(nombre);
    antiguedadEnMeses = antiguedad;
    puntuacion = 5.0f; // Valor inicial por defecto. El sufijo 'f' fuerza el literal como float (no double)

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
        listaAlojamientos[i] = otro.listaAlojamientos[i]; // Copia superficial (solo puntero)
    }
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

// Si se llena el arreglo, lo duplicamos
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
        listaAlojamientos[i]->mostrarReservasEnRango(desde, hasta);// '->' se usa para acceder a métodos desde un puntero
    }
}

// Anular reserva en todos sus alojamientos
void Anfitrion::anularReservacion(const char* codigoReserva) {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        listaAlojamientos[i]->eliminarReservacion(codigoReserva);
    }
}
