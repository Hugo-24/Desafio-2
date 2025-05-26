#include "Reserva.h"
#include "Alojamiento.h"
#include "Huesped.h"
#include "Funciones.h"

// Inicialización de contadores estáticos
int Reserva::siguienteId = 1;
int Reserva::totalReservasCreadas = 0;
int Reserva::totalIteracionesEnReservas = 0;

// Genera un código tipo RSV-0001 automáticamente
void Reserva::generarCodigo() {
    char buffer[10];
    buffer[0] = 'R';
    buffer[1] = 'S';
    buffer[2] = 'V';
    buffer[3] = '-';
    buffer[4] = (siguienteId / 1000) % 10 + '0';
    buffer[5] = (siguienteId / 100) % 10 + '0';
    buffer[6] = (siguienteId / 10) % 10 + '0';
    buffer[7] = (siguienteId % 10) + '0';
    buffer[8] = '\0';

    codigo = copiarTexto(buffer);  // Usa Funciones.h
    siguienteId++;
    totalReservasCreadas++;
}

// Constructor automático
Reserva::Reserva(const Fecha& fechaEnt, int dur, Alojamiento* aloj, Huesped* huesp,
                 const char* metPago, const Fecha& fechaPag, double mto, const char* anot)
    : fechaEntrada(fechaEnt), duracion(dur), alojamiento(aloj), huesped(huesp),
    fechaPago(fechaPag), monto(mto)
{
    generarCodigo();
    metodoPago = copiarTexto(metPago);
    anotaciones = copiarTexto(anot);
}

// Constructor con código manual (desde archivo)
Reserva::Reserva(const char* cod, const Fecha& fechaEnt, int dur, Alojamiento* aloj, Huesped* huesp,
                 const char* metPago, const Fecha& fechaPag, double mto, const char* anot)
    : fechaEntrada(fechaEnt), duracion(dur), alojamiento(aloj), huesped(huesp),
    fechaPago(fechaPag), monto(mto)
{
    codigo = copiarTexto(cod);
    metodoPago = copiarTexto(metPago);
    anotaciones = copiarTexto(anot);
    totalReservasCreadas++;
}

// Constructor de copia
Reserva::Reserva(const Reserva& otra)
    : fechaEntrada(otra.fechaEntrada), duracion(otra.duracion),
    alojamiento(otra.alojamiento), huesped(otra.huesped),
    fechaPago(otra.fechaPago), monto(otra.monto)
{
    codigo = copiarTexto(otra.codigo);
    metodoPago = copiarTexto(otra.metodoPago);
    anotaciones = copiarTexto(otra.anotaciones);
    totalReservasCreadas++;
}

// Operador de asignación
Reserva& Reserva::operator=(const Reserva& otra) {
    if (this != &otra) {
        delete[] codigo;
        delete[] metodoPago;
        delete[] anotaciones;

        fechaEntrada = otra.fechaEntrada;
        duracion = otra.duracion;
        alojamiento = otra.alojamiento;
        huesped = otra.huesped;
        fechaPago = otra.fechaPago;
        monto = otra.monto;

        codigo = copiarTexto(otra.codigo);
        metodoPago = copiarTexto(otra.metodoPago);
        anotaciones = copiarTexto(otra.anotaciones);
    }
    return *this;
}

// Destructor
Reserva::~Reserva() {
    delete[] codigo;
    delete[] metodoPago;
    delete[] anotaciones;
}

// Getters
const char* Reserva::getCodigo() const { return codigo; }
Fecha Reserva::getFechaEntrada() const { return fechaEntrada; }
int Reserva::getDuracion() const { return duracion; }
Alojamiento* Reserva::getAlojamiento() const { return alojamiento; }
Huesped* Reserva::getHuesped() const { return huesped; }
const char* Reserva::getMetodoPago() const { return metodoPago; }
Fecha Reserva::getFechaPago() const { return fechaPago; }
double Reserva::getMonto() const { return monto; }
const char* Reserva::getAnotaciones() const { return anotaciones; }

// Calcula la fecha de salida (fecha entrada + duración)
Fecha Reserva::calcularFechaSalida() const {
    return fechaEntrada + duracion;
}

// Imprime comprobante (formato simple)
void Reserva::mostrarComprobante() const {
    // (por implementar si deseas mostrar en consola o guardar en archivo)
}

// Acceso a contadores
int Reserva::getTotalReservasCreadas() {
    return totalReservasCreadas;
}

int Reserva::getTotalIteraciones() {
    return totalIteracionesEnReservas;
}

int Reserva::getSiguienteId() {
    return siguienteId;
}

void Reserva::setSiguienteId(int nuevoId) {
    siguienteId = nuevoId;
}
