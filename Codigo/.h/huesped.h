#ifndef HUESPED_H
#define HUESPED_H
#include <cstring>
#include <cstddef>

class Reserva;
class Alojamiento;

class Huesped {
private:
    static int siguienteId;
    char* codigo;
    char* nombreCompleto;
    char* documentoIdentidad;
    int antiguedadEnMeses;
    double puntuacionPromedio;
    Reserva** listaReservas;
    int cantidadReservas;
    int capacidadReservas;

    // Copia segura de texto dinámico
    char* copiarTexto(const char* texto) const {
        if (!texto) return nullptr;
        size_t len = std::strlen(texto);
        char* copia = new char[len + 1];
        strcpy(copia, texto);
        return copia;
    }

    // Redimensiona el arreglo de reservas (duplica la capacidad)
    void redimensionarReservas() {
        int nuevaCap = capacidadReservas * 2;
        Reserva** nuevoArreglo = new Reserva*[nuevaCap];
        for (int i = 0; i < cantidadReservas; i++) {
            nuevoArreglo[i] = listaReservas[i];
        }
        delete[] listaReservas;
        listaReservas = nuevoArreglo;
        capacidadReservas = nuevaCap;
    }

public:
    // Constructor principal (genera código automáticamente)
    Huesped(const char* nombre, const char* documento, int antiguedad, double puntuacion = 5.0);

    // Constructor de copia
    Huesped(const Huesped& otro);

    // Destructor
    ~Huesped();

    // Operador de asignación
    Huesped& operator=(const Huesped& otro);

    // Getters
    const char* getCodigo() const { return codigo; }
    const char* getNombreCompleto() const { return nombreCompleto; }
    const char* getDocumentoIdentidad() const { return documentoIdentidad; }
    int getAntiguedadEnMeses() const { return antiguedadEnMeses; }
    double getPuntuacionPromedio() const { return puntuacionPromedio; }
    int getCantidadReservas() const { return cantidadReservas; }
    // Retorna puntero a Reserva en posición index (o nullptr si fuera de rango)
    Reserva* getReserva(int index) const {
        if (index < 0 || index >= cantidadReservas) return nullptr;
        return listaReservas[index];
    }

    // Agrega una reserva al arreglo (sin dueño de memoria)
    void agregarReserva(Reserva* reserva);

    // Imprime resumen (nombre, documento, cantidad de reservas)
    void imprimirResumen() const;

    // Elimina una reservación por código
    void anularReservacion(const char* codigoReserva);

    // Muestra todas las reservaciones activas (comprobantes completos)
    void mostrarReservas() const;
};

#endif // HUESPED_H
