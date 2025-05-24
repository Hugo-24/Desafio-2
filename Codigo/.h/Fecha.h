#ifndef FECHA_H
#define FECHA_H

// Clase que representa una fecha en formato día/mes/año.
class Fecha {
private:
    int dia;   // Día del mes (1 a 31 según el mes)
    int mes;   // Mes del año (1 a 12)
    int anio;  // Año (ej. 2025)

    bool esValida(int d, int m, int a) const;
    bool esBisiesto(int a) const;
    void agregarDias(int dias);

public:
    // Constructor por defecto: crea la fecha 01/01/2000
    Fecha();

    // Constructor con parámetros: permite inicializar día, mes y año
    Fecha(int d, int m, int a);

    // Constructor de copia: crea una nueva instancia a partir de otra Fecha
    Fecha(const Fecha& otra);

    // Destructor: no gestiona memoria dinámica, pero se define por buenas prácticas
    ~Fecha();

    // Métodos de acceso (getters)
    // Devuelven el valor del día, mes o año actual
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    // Métodos de modificación (setters)
    // Permiten cambiar el valor del día, mes o año
    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);

    // Convierte la fecha en una cadena de texto tipo "DD/MM/AAAA"
    // IMPORTANTE: El puntero retornado debe ser liberado con delete[]
    char* toString() const;

    // Operador de igualdad: compara si dos fechas son iguales
    bool operator==(const Fecha& otra) const;

    // Operador menor que: determina si una fecha es anterior a otra
    bool operator<(const Fecha& otra) const;
    // Operador mayor que: determina si una fecha es posterior a otra
    bool operator>(const Fecha& otra) const;

    //operadores para verificar rango
    bool operator<=(const Fecha& otra) const;
    bool operator>=(const Fecha& otra) const;

    Fecha operator+(int dias) const;
    Fecha& operator=(const Fecha& otra);
    bool esValida() const;

};

#endif
