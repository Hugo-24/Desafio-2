#include "Huesped.h"
#include "Reserva.h"
#include "Alojamiento.h"

// Inicialización de contadores
int Huesped::siguienteId = 1;
int Huesped::totalHuespedesCreados = 0;
int Huesped::totalIteracionesEnReservas = 0;

// Función auxiliar: calcula la longitud de un texto
int Huesped::longitudTexto(const char* texto) const {
    int i = 0;
    while (texto[i] != '\0') {
        i++;
        totalIteracionesEnReservas++;
    }
    return i;
}

// Función auxiliar: copia texto
void Huesped::copiarTexto(char* destino, const char* fuente) const {
    int i = 0;
    while (fuente[i] != '\0') {
        destino[i] = fuente[i];
        i++;
        totalIteracionesEnReservas++;
    }
    destino[i] = '\0';
}

// Función auxiliar: crea una nueva copia dinámica de texto
char* Huesped::copiarTexto(const char* fuente) const {
    if (!fuente) return nullptr;
    int len = longitudTexto(fuente);
    char* copia = new char[len + 1];
    copiarTexto(copia, fuente);
    return copia;
}

// Función auxiliar: compara si dos textos son iguales
bool Huesped::sonIguales(const char* a, const char* b) const {
    if (!a || !b) return false;
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        totalIteracionesEnReservas++;
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

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
    cantidadReservas(0), capacidadReservas(5)
{
    generarCodigo();
    nombreCompleto = copiarTexto(nombre);
    documentoIdentidad = copiarTexto(documento);
    listaReservas = new Reserva*[capacidadReservas];
}

// Constructor de copia
Huesped::Huesped(const Huesped& otro)
    : antiguedadEnMeses(otro.antiguedadEnMeses), puntuacionPromedio(otro.puntuacionPromedio),
    cantidadReservas(otro.cantidadReservas), capacidadReservas(otro.capacidadReservas)
{
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
    int nuevaCap = capacidadReservas * 2;
    Reserva** nuevo = new Reserva*[nuevaCap];
    for (int i = 0; i < cantidadReservas; i++) {
        nuevo[i] = listaReservas[i];
        totalIteracionesEnReservas++;
    }
    delete[] listaReservas;
    listaReservas = nuevo;
    capacidadReservas = nuevaCap;
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

// Elimina reserva por código
void Huesped::anularReservacion(const char* codigoRes) {
    for (int i = 0; i < cantidadReservas; i++) {
        totalIteracionesEnReservas++;
        if (sonIguales(listaReservas[i]->getCodigo(), codigoRes)) {
            Alojamiento* aloj = listaReservas[i]->getAlojamiento();
            if (aloj) aloj->eliminarReservacion(codigoRes);
            delete listaReservas[i];
            for (int j = i; j < cantidadReservas - 1; j++) {
                listaReservas[j] = listaReservas[j + 1];
            }
            cantidadReservas--;
            return;
        }
    }
}

// Imprime resumen (puedes adaptar impresión real)
void Huesped::imprimirResumen() const {
    // Aquí deberías imprimir los datos (por consola o archivo según se use)
}

// Muestra comprobantes de todas sus reservas
void Huesped::mostrarReservas() const {
    for (int i = 0; i < cantidadReservas; i++) {
        listaReservas[i]->mostrarComprobante();
    }
}

// Contadores
int Huesped::getTotalHuespedesCreados() {
    return totalHuespedesCreados;
}

int Huesped::getTotalIteraciones() {
    return totalIteracionesEnReservas;
}
