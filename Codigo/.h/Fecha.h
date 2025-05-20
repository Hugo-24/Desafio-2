#ifndef FECHA_H
#define FECHA_H

class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    // Constructores
    Fecha();                      // Por defecto: 01/01/2000
    Fecha(int d, int m, int a);   // Con parámetros
    Fecha(const Fecha& otra);     // Copia

    // Destructor
    ~Fecha();

    // Getters
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    // Setters
    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);

    // Utilidades
    char* toString() const;

    // Operadores
    bool operator==(const Fecha& otra) const;
    bool operator<(const Fecha& otra) const;
};

#endif // FECHA_H
