#include "Reserva.h"
#include "Alojamiento.h"
#include "Huesped.h"
#include "Funciones.h"
#include <iostream>


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

// Algoritmo para el día de la semana (Zeller)
static int calcularDiaSemana(int d, int m, int y) {
    if (m < 3) { m += 12; y -= 1; }
    int K = y % 100;
    int J = y / 100;
    int q = d;
    int h = (q + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
    return h; // 0=sábado, 1=domingo, 2=lunes, ..., 6=viernes
}
// Imprime comprobante (formato simple)
void Reserva::mostrarComprobante() const {
    int dE = fechaEntrada.getDia();
    int mE = fechaEntrada.getMes();
    int aE = fechaEntrada.getAnio();
    int hE = calcularDiaSemana(dE, mE, aE);

    Fecha fS = calcularFechaSalida();
    int dS = fS.getDia();
    int mS = fS.getMes();
    int aS = fS.getAnio();
    int hS = calcularDiaSemana(dS, mS, aS);

    static const char* diasSemana[] = {
        "sabado", "domingo", "lunes", "martes",
        "miercoles", "jueves", "viernes"
    };
    static const char* meses[] = {
        "enero","febrero","marzo","abril","mayo","junio",
        "julio","agosto","septiembre","octubre","noviembre","diciembre"
    };

    std::cout << "----- Comprobante de Reserva -----\n";
    std::cout << "Codigo: " << (codigo ? codigo : "-") << "\n";
    std::cout << "Fecha de entrada: " << diasSemana[hE]
              << ", " << dE << " de " << meses[mE - 1]
              << " de " << aE << "\n";
    std::cout << "Fecha de salida:  " << diasSemana[hS]
              << ", " << dS << " de " << meses[mS - 1]
              << " de " << aS << "\n";
    if (metodoPago) {
        std::cout << "Metodo de pago:   " << metodoPago << "\n";
        std::cout << "Fecha de pago:    "
                  << fechaPago.getDia() << "/" << fechaPago.getMes()
                  << "/" << fechaPago.getAnio() << "\n";
        std::cout << "Monto pagado:     " << monto << "\n";
    }
    if (anotaciones) {
        std::cout << "Anotaciones:      " << anotaciones << "\n";
    }
    std::cout << "---------------------------------\n";
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
