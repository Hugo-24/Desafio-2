// Huesped.cpp
#include "Huesped.h"
#include "Reserva.h"
#include "Alojamiento.h"
#include <cstring>
#include <cstdio>
#include <iostream>

int Huesped::siguienteId = 1;

// Constructor principal (genera código automáticamente)
Huesped::Huesped(const char* nombre, const char* documento, int antiguedad, double puntuacion)
    : antiguedadEnMeses(antiguedad), puntuacionPromedio(puntuacion),
    cantidadReservas(0), capacidadReservas(5)
{
    // Generar código único (HSP-0001, HSP-0002, ...)
    char buf[16];
    std::snprintf(buf, sizeof(buf), "HSP-%04d", siguienteId++);
    codigo = new char[std::strlen(buf) + 1];
    std::strcpy(codigo, buf);

    nombreCompleto = copiarTexto(nombre);
    documentoIdentidad = copiarTexto(documento);

    listaReservas = new Reserva*[capacidadReservas];
}

// Constructor de copia
Huesped::Huesped(const Huesped& otro)
    : antiguedadEnMeses(otro.antiguedadEnMeses),
    puntuacionPromedio(otro.puntuacionPromedio),
    cantidadReservas(otro.cantidadReservas),
    capacidadReservas(otro.capacidadReservas)
{
    // Copiar código
    if (otro.codigo) {
        codigo = new char[std::strlen(otro.codigo) + 1];
        std::strcpy(codigo, otro.codigo);
    } else {
        codigo = nullptr;
    }

    // Copiar nombre y documento
    nombreCompleto = copiarTexto(otro.nombreCompleto);
    documentoIdentidad = copiarTexto(otro.documentoIdentidad);

    // Copiar arreglo de reservas (punteros)
    listaReservas = new Reserva*[capacidadReservas];
    for (int i = 0; i < cantidadReservas; i++) {
        listaReservas[i] = otro.listaReservas[i];
    }
}

// Destructor
Huesped::~Huesped() {
    delete[] codigo;
    delete[] nombreCompleto;
    delete[] documentoIdentidad;
    delete[] listaReservas;
}

// Operador de asignación
Huesped& Huesped::operator=(const Huesped& otro) {
    if (this != &otro) {
        // Liberar memoria actual
        delete[] codigo;
        delete[] nombreCompleto;
        delete[] documentoIdentidad;
        delete[] listaReservas;

        // Copiar valores primitivos
        antiguedadEnMeses = otro.antiguedadEnMeses;
        puntuacionPromedio = otro.puntuacionPromedio;
        cantidadReservas = otro.cantidadReservas;
        capacidadReservas = otro.capacidadReservas;

        // Copiar código
        if (otro.codigo) {
            codigo = new char[std::strlen(otro.codigo) + 1];
            std::strcpy(codigo, otro.codigo);
        } else {
            codigo = nullptr;
        }

        // Copiar nombre y documento
        nombreCompleto = copiarTexto(otro.nombreCompleto);
        documentoIdentidad = copiarTexto(otro.documentoIdentidad);

        // Copiar arreglo de reservas
        listaReservas = new Reserva*[capacidadReservas];
        for (int i = 0; i < cantidadReservas; i++) {
            listaReservas[i] = otro.listaReservas[i];
        }
    }
    return *this;
}

// Agrega una reserva al arreglo (sin dueño de memoria)
void Huesped::agregarReserva(Reserva* reserva) {
    // Validar que no haya conflicto de fechas
    Fecha newStart = reserva->getFechaEntrada();
    Fecha newEnd   = reserva->calcularFechaSalida();
    for (int i = 0; i < cantidadReservas; i++) {
        Fecha exStart = listaReservas[i]->getFechaEntrada();
        Fecha exEnd   = listaReservas[i]->calcularFechaSalida();
        if (!(newEnd <= exStart || exEnd <= newStart)) {
            std::cout << "Error: Conflicto de fechas con reservacion existente.\n";
            return;
        }
    }
    // Redimensionar si es necesario
    if (cantidadReservas == capacidadReservas) {
        redimensionarReservas();
    }
    listaReservas[cantidadReservas++] = reserva;
}


// Imprime resumen (nombre, documento, cantidad de reservas)
void Huesped::imprimirResumen() const {
    std::cout << "Huesped: " << nombreCompleto
              << ", Documento: " << documentoIdentidad
              << ", Reservas: " << cantidadReservas << std::endl;
}

// Elimina una reservación por código
void Huesped::anularReservacion(const char* codigoReserva) {
    for (int i = 0; i < cantidadReservas; i++) {
        if (std::strcmp(listaReservas[i]->getCodigo(), codigoReserva) == 0) {
            // Primero notificar al alojamiento
            Alojamiento* aloj = listaReservas[i]->getAlojamiento();
            if (aloj) {
                aloj->eliminarReservacion(codigoReserva);
            }
            // Compactar el arreglo
            for (int j = i; j < cantidadReservas - 1; j++) {
                listaReservas[j] = listaReservas[j+1];
            }
            cantidadReservas--;
            std::cout << "Reservacion con codigo " << codigoReserva << " anulada en Huesped.\n";
            return;
        }
    }
    std::cout << "Reservacion con codigo " << codigoReserva << " no encontrada.\n";
}

// Muestra comprobantes de todas las reservas
void Huesped::mostrarReservas() const {
    for (int i = 0; i < cantidadReservas; i++) {
        listaReservas[i]->mostrarComprobante();
    }
}
