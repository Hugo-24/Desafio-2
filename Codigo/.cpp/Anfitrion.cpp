#include "Anfitrion.h"
#include "Alojamiento.h"
#include <iostream>

using namespace std;

// Inicialización de variables estáticas
int Anfitrion::contadorAnfitriones = 0;
int Anfitrion::totalAnfitrionesCreados = 0;
int Anfitrion::totalIteracionesEnAlojamientos = 0;

// Función auxiliar para calcular la longitud de un texto (como strlen)
int Anfitrion::longitudTexto(const char* texto) const {
    int len = 0;
    while (texto[len] != '\0') {
        len++;
    }
    return len;
}

// Función auxiliar para copiar texto de forma manual (sin usar strncpy)
void Anfitrion::copiarTexto(char* destino, const char* fuente) const {
    int i = 0;
    while (fuente[i] != '\0') {
        destino[i] = fuente[i];
        i++;
    }
    destino[i] = '\0';
}

// Copia segura de texto dinámico
char* Anfitrion::copiarTexto(const char* texto) const {
    int longitud = longitudTexto(texto);
    char* copia = new char[longitud + 1];
    copiarTexto(copia, texto);
    return copia;
}

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

// Esta función duplica el tamaño del arreglo de alojamientos cuando ya no hay más espacio.
// Es necesaria porque usamos arreglos dinámicos sin STL, así que debemos manejar manualmente
// el crecimiento de la estructura para seguir agregando alojamientos sin perder los anteriores.
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
void Anfitrion::anularReservacion(const char* codigoReserva) {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        totalIteracionesEnAlojamientos++;
        listaAlojamientos[i]->eliminarReservacion(codigoReserva);
    }
}

// Reporte de uso de recursos
int Anfitrion::getTotalAnfitrionesCreados() {
    return totalAnfitrionesCreados;
}

int Anfitrion::getTotalIteraciones() {
    return totalIteracionesEnAlojamientos;
}
