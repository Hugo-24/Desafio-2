#include "Reserva.h"
#include <cstring>
#include <cstdio>
#include <iostream>

// Inicializar contador estático
int Reserva::siguienteId = 1;

// Algoritmo para el día de la semana (Zeller)
static int calcularDiaSemana(int d, int m, int y) {
    if (m < 3) { m += 12; y -= 1; }
    int K = y % 100;
    int J = y / 100;
    int q = d;
    int h = (q + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
    return h; // 0=sábado, 1=domingo, 2=lunes, ..., 6=viernes
}

// Constructor automático: genera código internamente (RSV-0001, RSV-0002...)
Reserva::Reserva(const Fecha& fechaEnt, int dur,
                 Alojamiento* aloj, Huesped* huesp,
                 int metPago, const Fecha& fechaPag,
                 double mto, const char* anot) :
    fechaEntrada(fechaEnt),
    duracion(dur),
    alojamiento(aloj),
    huesped(huesp),
    metodoPago(metPago),
    fechaPago(fechaPag),
    monto(mto)
{
    // Generar código único
    char buf[16];
    std::snprintf(buf, sizeof(buf), "RSV-%04d", siguienteId++);
    codigo = new char[std::strlen(buf) + 1];
    std::strcpy(codigo, buf);

    // Anotaciones
    if (anot) {
        anotaciones = new char[std::strlen(anot) + 1];
        std::strcpy(anotaciones, anot);
    } else {
        anotaciones = nullptr;
    }
}

// Constructor completo (código manual)
Reserva::Reserva(const char* cod, const Fecha& fechaEnt, int dur,
                 Alojamiento* aloj, Huesped* huesp,
                 int metPago, const Fecha& fechaPag,
                 double mto, const char* anot) :
    fechaEntrada(fechaEnt),
    duracion(dur),
    alojamiento(aloj),
    huesped(huesp),
    metodoPago(metPago),
    fechaPago(fechaPag),
    monto(mto)
{
    // Código manual
    if (cod) {
        codigo = new char[std::strlen(cod) + 1];
        std::strcpy(codigo, cod);
    } else {
        codigo = nullptr;
    }
    // Anotaciones
    if (anot) {
        anotaciones = new char[std::strlen(anot) + 1];
        std::strcpy(anotaciones, anot);
    } else {
        anotaciones = nullptr;
    }
}

// Constructor de copia
Reserva::Reserva(const Reserva& other) :
    fechaEntrada(other.fechaEntrada),
    duracion(other.duracion),
    alojamiento(other.alojamiento),
    huesped(other.huesped),
    metodoPago(other.metodoPago),
    fechaPago(other.fechaPago),
    monto(other.monto)
{
    // Copiar código
    if (other.codigo) {
        codigo = new char[std::strlen(other.codigo) + 1];
        std::strcpy(codigo, other.codigo);
    } else {
        codigo = nullptr;
    }
    // Copiar anotaciones
    if (other.anotaciones) {
        anotaciones = new char[std::strlen(other.anotaciones) + 1];
        std::strcpy(anotaciones, other.anotaciones);
    } else {
        anotaciones = nullptr;
    }
}

// Operador de asignación
Reserva& Reserva::operator=(const Reserva& other) {
    if (this != &other) {
        delete[] codigo;
        delete[] anotaciones;

        fechaEntrada = other.fechaEntrada;
        duracion = other.duracion;
        alojamiento = other.alojamiento;
        huesped = other.huesped;
        metodoPago   = other.metodoPago;
        fechaPago = other.fechaPago;
        monto = other.monto;

        // Copiar código
        if (other.codigo) {
            codigo = new char[std::strlen(other.codigo) + 1];
            std::strcpy(codigo, other.codigo);
        } else {
            codigo = nullptr;
        }

        // Copiar anotaciones
        if (other.anotaciones) {
            anotaciones = new char[std::strlen(other.anotaciones) + 1];
            std::strcpy(anotaciones, other.anotaciones);
        } else {
            anotaciones = nullptr;
        }
    }
    return *this;
}

// Destructor
Reserva::~Reserva() {
    delete[] codigo;
    delete[] anotaciones;
}

// Getters
const char* Reserva::getCodigo() const { return codigo; }
Fecha Reserva::getFechaEntrada() const { return fechaEntrada; }
int Reserva::getDuracion() const { return duracion; }
Alojamiento* Reserva::getAlojamiento() const { return alojamiento; }
Huesped* Reserva::getHuesped() const { return huesped; }
int Reserva::getMetodoPago() const { return metodoPago; }
Fecha Reserva::getFechaPago() const { return fechaPago; }
double Reserva::getMonto() const { return monto; }
const char* Reserva::getAnotaciones() const { return anotaciones; }

// Calcula la fecha de salida sumando la duración
Fecha Reserva::calcularFechaSalida() const {
    return fechaEntrada + duracion;
}

// Muestra comprobante con día de semana y fecha textual
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
