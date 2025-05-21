#include "Fecha.h"
// Constructor por defecto
Fecha::Fecha() {
    dia = 1;
    mes = 1;
    anio = 2000;
}

// Constructor con parámetros
Fecha::Fecha(int d, int m, int a) {
    if (esValida(d, m, a)) {
        dia = d;
        mes = m;
        anio = a;
    } else {
        // Fecha por defecto en caso de inválida
        dia = 1;
        mes = 1;
        anio = 2000;
    }
}

// Constructor de copia
Fecha::Fecha(const Fecha& otra) {
    dia = otra.dia;
    mes = otra.mes;
    anio = otra.anio;
}

// Destructor (no hay memoria dinámica interna)
Fecha::~Fecha() { }

// Getters
int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

// Setters
void Fecha::setDia(int d) {
    if (esValida(d, mes, anio)) {
        dia = d;
    }
}

void Fecha::setMes(int m) {
    if (esValida(dia, m, anio)) {
        mes = m;
    }
}

void Fecha::setAnio(int a) {
    if (esValida(dia, mes, a)) {
        anio = a;
    }
}

// Devuelve la fecha como "DD/MM/AAAA"
char* Fecha::toString() const {
    char* texto = new char[11]; // DD/MM/AAAA + '\0'

    texto[0] = (dia / 10) + '0';
    texto[1] = (dia % 10) + '0';
    texto[2] = '/';
    texto[3] = (mes / 10) + '0';
    texto[4] = (mes % 10) + '0';
    texto[5] = '/';
    texto[6] = ((anio / 1000) % 10) + '0';
    texto[7] = ((anio / 100) % 10) + '0';
    texto[8] = ((anio / 10) % 10) + '0';
    texto[9] = (anio % 10) + '0';
    texto[10] = '\0';

    return texto;
}

// Comparación de igualdad
bool Fecha::operator==(const Fecha& otra) const {
    return dia == otra.dia && mes == otra.mes && anio == otra.anio;
}

// Comparación menor que
bool Fecha::operator<(const Fecha& otra) const {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;
    return dia < otra.dia;
}
bool Fecha::operator<=(const Fecha& otra) const {
    return (*this < otra) || (*this == otra);
}

bool Fecha::operator>=(const Fecha& otra) const {
    return (otra < *this) || (*this == otra);
}

// Operador de suma de días
Fecha Fecha::operator+(int dias) const {
    Fecha resultado(*this);
    resultado.agregarDias(dias);
    return resultado;
}

// Operador de asignacion
Fecha& Fecha::operator=(const Fecha& otra) {
    if (this != &otra) {
        dia = otra.dia;
        mes = otra.mes;
        anio = otra.anio;
    }
    return *this;
}

bool Fecha::esValida() const {
    return esValida(dia, mes, anio);
}
// Métodos auxiliares privados
bool Fecha::esBisiesto(int a) const {
    return (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
}

bool Fecha::esValida(int d, int m, int a) const {
    if (a < 1 || m < 1 || m > 12 || d < 1) return false;

    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (esBisiesto(a)) {
        diasPorMes[1] = 29;
    }

    return d <= diasPorMes[m - 1];
}

void Fecha::agregarDias(int dias) {
    static const int diasPorMesNormales[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    while (dias > 0) {
        int diasEnMes = diasPorMesNormales[mes - 1];
        if (mes == 2 && esBisiesto(anio)) {
            diasEnMes = 29;
        }

        int diasRestantesEnMes = diasEnMes - dia;

        if (dias <= diasRestantesEnMes) {
            dia += dias;
            dias = 0;
        } else {
            dias -= (diasRestantesEnMes + 1);
            dia = 1;
            mes++;
            if (mes > 12) {
                mes = 1;
                anio++;
            }
        }
    }
}
