#include "Huesped.h"
#include "Reserva.h"
#include "Funciones.h"

// Inicialización de contadores
int Huesped::siguienteId = 1;
int Huesped::totalHuespedesCreados = 0;
int Huesped::totalIteracionesEnReservas = 0;

// Genera código tipo HSP-0001
void Huesped::generarCodigo() {
    char buffer[10];
    buffer[0] = 'H';
    buffer[1] = 'S';
    buffer[2] = 'P';
    buffer[3] = '-';
    buffer[4] = (siguienteId / 1000) % 10 + '0';
    buffer[5] = (siguienteId / 100) % 10 + '0';
    buffer[6] = (siguienteId / 10) % 10 + '0';
    buffer[7] = (siguienteId % 10) + '0';
    buffer[8] = '\0';

    codigo = copiarTexto(buffer);
    siguienteId++;
    totalHuespedesCreados++;
}

// Constructor principal
Huesped::Huesped(const char* nombre, const char* documento, int antiguedad, double puntuacion)
    : antiguedadEnMeses(antiguedad), puntuacionPromedio(puntuacion),
    cantidadReservas(0), capacidadReservas(5) {
    generarCodigo();
    nombreCompleto = copiarTexto(nombre);
    documentoIdentidad = copiarTexto(documento);
    listaReservas = new Reserva*[capacidadReservas];
}

// Constructor de copia
Huesped::Huesped(const Huesped& otro)
    : antiguedadEnMeses(otro.antiguedadEnMeses), puntuacionPromedio(otro.puntuacionPromedio),
    cantidadReservas(otro.cantidadReservas), capacidadReservas(otro.capacidadReservas) {
    codigo = copiarTexto(otro.codigo);
    nombreCompleto = copiarTexto(otro.nombreCompleto);
    documentoIdentidad = copiarTexto(otro.documentoIdentidad);

    listaReservas = new Reserva*[capacidadReservas];
    for (int i = 0; i < cantidadReservas; i++) {
        listaReservas[i] = otro.listaReservas[i];
    }

    totalHuespedesCreados++;
}

// Operador de asignación
Huesped& Huesped::operator=(const Huesped& otro) {
    if (this != &otro) {
        delete[] codigo;
        delete[] nombreCompleto;
        delete[] documentoIdentidad;
        delete[] listaReservas;

        antiguedadEnMeses = otro.antiguedadEnMeses;
        puntuacionPromedio = otro.puntuacionPromedio;
        cantidadReservas = otro.cantidadReservas;
        capacidadReservas = otro.capacidadReservas;

        codigo = copiarTexto(otro.codigo);
        nombreCompleto = copiarTexto(otro.nombreCompleto);
        documentoIdentidad = copiarTexto(otro.documentoIdentidad);

        listaReservas = new Reserva*[capacidadReservas];
        for (int i = 0; i < cantidadReservas; i++) {
            listaReservas[i] = otro.listaReservas[i];
        }
    }
    return *this;
}

// Destructor
Huesped::~Huesped() {
    delete[] codigo;
    delete[] nombreCompleto;
    delete[] documentoIdentidad;
    delete[] listaReservas;
}

// Redimensiona el arreglo de reservas (duplica capacidad)
void Huesped::redimensionarReservas() {
    listaReservas = redimensionarArreglo(listaReservas, cantidadReservas, capacidadReservas);
}

// Accesores
const char* Huesped::getCodigo() const { return codigo; }
const char* Huesped::getNombreCompleto() const { return nombreCompleto; }
const char* Huesped::getDocumentoIdentidad() const { return documentoIdentidad; }
int Huesped::getAntiguedadEnMeses() const { return antiguedadEnMeses; }
double Huesped::getPuntuacionPromedio() const { return puntuacionPromedio; }
int Huesped::getCantidadReservas() const { return cantidadReservas; }

Reserva* Huesped::getReserva(int indice) const {
    if (indice < 0 || indice >= cantidadReservas) return nullptr;
    return listaReservas[indice];
}

// Agrega reserva si no hay solapamiento
void Huesped::agregarReserva(Reserva* reserva) {
    Fecha nuevaInicio = reserva->getFechaEntrada();
    Fecha nuevaFin = reserva->calcularFechaSalida();

    for (int i = 0; i < cantidadReservas; i++) {
        totalIteracionesEnReservas++;
        Fecha exIni = listaReservas[i]->getFechaEntrada();
        Fecha exFin = listaReservas[i]->calcularFechaSalida();

        if (!(nuevaFin <= exIni || exFin <= nuevaInicio)) {
            return; // Conflicto de fechas
        }
    }

    if (cantidadReservas == capacidadReservas) {
        redimensionarReservas();
    }
    listaReservas[cantidadReservas++] = reserva;
}

// Elimina reserva por fecha y duración
void Huesped::anularReservacion(const Fecha& fecha, int duracion) {
    for (int i = 0; i < cantidadReservas; i++) {
        totalIteracionesEnReservas++;

        Fecha ini = listaReservas[i]->getFechaEntrada();
        int dur = listaReservas[i]->getDuracion();

        if (ini == fecha && dur == duracion) {
            for (int j = i; j < cantidadReservas - 1; j++) {
                listaReservas[j] = listaReservas[j + 1];
            }
            cantidadReservas--;
            return;
        }
    }
}

// Muestra resumen
void Huesped::imprimirResumen() const {
    // Puedes implementar impresión de datos generales si se requiere
}

// Muestra comprobantes
void Huesped::mostrarReservas() const {
    for (int i = 0; i < cantidadReservas; i++) {
        listaReservas[i]->mostrarComprobante();
    }
}

// Verifica si el huesped ya tiene una reserva que se cruce con el nuevo intento de reserva
bool Huesped::verificaCruce(const Fecha& inicio, int duracion) const {
    Fecha finNueva = inicio + (duracion - 1);
    for (int i = 0; i < cantidadReservas; i++) {
        Fecha entradaExistente = listaReservas[i]->getFechaEntrada();
        int duracionExistente = listaReservas[i]->getDuracion();
        Fecha finExistente = entradaExistente + (duracionExistente - 1);

        // Si se cruzan las fechas: hay conflicto
        if (!(finNueva < entradaExistente || finExistente < inicio)) {
            return true;
        }
    }
    return false;
}

// Contadores
int Huesped::getTotalHuespedesCreados() {
    return totalHuespedesCreados;
}

int Huesped::getTotalIteraciones() {
    return totalIteracionesEnReservas;
}
