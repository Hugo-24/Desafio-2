#include "Reserva.h"
#include "Alojamiento.h"
#include "Huesped.h"

// Inicialización de contadores estáticos
int Reserva::siguienteId = 1;
int Reserva::totalReservasCreadas = 0;
int Reserva::totalIteracionesEnReservas = 0;

// Función auxiliar: calcula longitud de texto
int Reserva::longitudTexto(const char* texto) const {
    int i = 0;
    while (texto[i] != '\0') {
        i++;
        totalIteracionesEnReservas++;
    }
    return i;
}

// Función auxiliar: copia de texto (como strcpy)
void Reserva::copiarTexto(char* destino, const char* fuente) const {
    int i = 0;
    while (fuente[i] != '\0') {
        destino[i] = fuente[i];
        i++;
        totalIteracionesEnReservas++;
    }
    destino[i] = '\0';
}

// Función auxiliar: crea una copia nueva de texto
char* Reserva::copiarTexto(const char* fuente) const {
    if (!fuente) return nullptr;
    int len = longitudTexto(fuente);
    char* copia = new char[len + 1];
    copiarTexto(copia, fuente);
    return copia;
}

// Función auxiliar: compara si dos textos son iguales
bool Reserva::sonIguales(const char* a, const char* b) const {
    if (!a || !b) return false;
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        totalIteracionesEnReservas++;
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

// Genera un código tipo RSV-0001
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

    codigo = copiarTexto(buffer);
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

// Constructor con código manual (por ejemplo, desde archivo)
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

// Calcula la fecha de salida
Fecha Reserva::calcularFechaSalida() const {
    return fechaEntrada + duracion;
}

// Imprime comprobante (formato simple sin iostream)
void Reserva::mostrarComprobante() const {
    // Esta función debería redirigirse a un sistema de impresión de consola
    // adecuado al proyecto. Aquí solo se declara.
}

// Acceso a contadores
int Reserva::getTotalReservasCreadas() {
    return totalReservasCreadas;
}

int Reserva::getTotalIteraciones() {
    return totalIteracionesEnReservas;
}
