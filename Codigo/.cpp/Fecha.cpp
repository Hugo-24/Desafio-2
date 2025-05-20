#include "Fecha.h"
// Constructor por defecto
Fecha::Fecha() {
    dia = 1;
    mes = 1;
    anio = 2000;
}

// Constructor con parámetros
Fecha::Fecha(int d, int m, int a) {
    dia = d;
    mes = m;
    anio = a;
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
void Fecha::setDia(int d) { dia = d; }
void Fecha::setMes(int m) { mes = m; }
void Fecha::setAnio(int a) { anio = a; }

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
