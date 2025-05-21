#include "Alojamiento.h"
#include "Anfitrion.h"
#include <iostream>
#include <cstring>

using namespace std;

// Copia segura de texto dinámico
char* Alojamiento::copiarTexto(const char* texto) const {
    size_t longitud = strlen(texto);
    char* copia = new char[longitud + 1];
    strncpy(copia, texto, longitud);
    copia[longitud] = '\0';
    return copia;
}

// Redimensiona los arreglos si se llenan
void Alojamiento::redimensionarReservas() {
    int nuevaCapacidad = capacidadReservaciones * 2;
    Fecha* nuevasFechas = new Fecha[nuevaCapacidad];
    int* nuevasDuraciones = new int[nuevaCapacidad];

    for (int i = 0; i < cantidadReservaciones; i++) {
        nuevasFechas[i] = fechasInicioReservadas[i];
        nuevasDuraciones[i] = duracionesReservadas[i];
    }

    delete[] fechasInicioReservadas;
    delete[] duracionesReservadas;
    fechasInicioReservadas = nuevasFechas;
    duracionesReservadas = nuevasDuraciones;
    capacidadReservaciones = nuevaCapacidad;
}

// Constructor principal
Alojamiento::Alojamiento(const char* cod, const char* nom, const char* dep, const char* mun,
                         const char* dir, int tipo, double precio, Anfitrion* duenoPtr) {
    codigo = copiarTexto(cod);
    nombre = copiarTexto(nom);
    departamento = copiarTexto(dep);
    municipio = copiarTexto(mun);
    direccion = copiarTexto(dir);

    tipoAlojamiento = tipo;
    precioPorNoche = precio;
    dueno = duenoPtr;
    amenidades = 0;

    capacidadReservaciones = 10;
    cantidadReservaciones = 0;
    fechasInicioReservadas = new Fecha[capacidadReservaciones];
    duracionesReservadas = new int[capacidadReservaciones];
}

// Constructor de copia
Alojamiento::Alojamiento(const Alojamiento& otro) {
    codigo = copiarTexto(otro.codigo);
    nombre = copiarTexto(otro.nombre);
    departamento = copiarTexto(otro.departamento);
    municipio = copiarTexto(otro.municipio);
    direccion = copiarTexto(otro.direccion);

    tipoAlojamiento = otro.tipoAlojamiento;
    precioPorNoche = otro.precioPorNoche;
    dueno = otro.dueno;
    amenidades = otro.amenidades;

    capacidadReservaciones = otro.capacidadReservaciones;
    cantidadReservaciones = otro.cantidadReservaciones;

    fechasInicioReservadas = new Fecha[capacidadReservaciones];
    duracionesReservadas = new int[capacidadReservaciones];

    for (int i = 0; i < cantidadReservaciones; i++) {
        fechasInicioReservadas[i] = otro.fechasInicioReservadas[i];
        duracionesReservadas[i] = otro.duracionesReservadas[i];
    }
}

// Destructor
Alojamiento::~Alojamiento() {
    delete[] codigo;
    delete[] nombre;
    delete[] departamento;
    delete[] municipio;
    delete[] direccion;
    delete[] fechasInicioReservadas;
    delete[] duracionesReservadas;
}

// Getters
char* Alojamiento::getCodigo() const { return copiarTexto(codigo); }
char* Alojamiento::getNombre() const { return copiarTexto(nombre); }
char* Alojamiento::getDepartamento() const { return copiarTexto(departamento); }
char* Alojamiento::getMunicipio() const { return copiarTexto(municipio); }
char* Alojamiento::getDireccion() const { return copiarTexto(direccion); }
int Alojamiento::getTipoAlojamiento() const { return tipoAlojamiento; }
double Alojamiento::getPrecioPorNoche() const { return precioPorNoche; }
int Alojamiento::getAmenidades() const { return amenidades; }

// Amenidades como bits
bool Alojamiento::tieneAmenidad(int amenidad) const {
    return (amenidades & (1 << amenidad)) != 0;
}

void Alojamiento::agregarAmenidad(int amenidad) {
    amenidades |= (1 << amenidad);
}

void Alojamiento::quitarAmenidad(int amenidad) {
    amenidades &= ~(1 << amenidad);
}

void Alojamiento::mostrarAmenidades() const {
    cout << "Amenidades activas:\n";
    if (tieneAmenidad(0)) cout << "- Wifi\n";
    if (tieneAmenidad(1)) cout << "- Piscina\n";
    if (tieneAmenidad(2)) cout << "- Parqueadero\n";
    if (tieneAmenidad(3)) cout << "- Cocina\n";
}

// Disponibilidad: no hay reservas en esa fecha exacta
bool Alojamiento::estaDisponible(const Fecha& inicio) const {
    for (int i = 0; i < cantidadReservaciones; i++) {
        if (inicio == fechasInicioReservadas[i]) return false;
    }
    return true;
}

// Agregar nueva reserva
void Alojamiento::agregarReservacion(const Fecha& inicio, int duracion) {
    if (cantidadReservaciones == capacidadReservaciones) {
        redimensionarReservas();
    }
    fechasInicioReservadas[cantidadReservaciones] = inicio;
    duracionesReservadas[cantidadReservaciones] = duracion;
    cantidadReservaciones++;
}

// Simular eliminación
void Alojamiento::eliminarReservacion(const char* codigoReserva) {
    cout << "Reserva con codigo " << codigoReserva << " eliminada del alojamiento " << nombre << " (simulado).\n";
}

// Mostrar reservas en rango
void Alojamiento::mostrarReservasEnRango(const Fecha& desde, const Fecha& hasta) const {
    cout << "Reservas del alojamiento '" << nombre << "' entre ";
    cout << desde.getDia() << "/" << desde.getMes() << "/" << desde.getAnio();
    cout << " y ";
    cout << hasta.getDia() << "/" << hasta.getMes() << "/" << hasta.getAnio() << ":\n";

    for (int i = 0; i < cantidadReservaciones; i++) {
        const Fecha& entrada = fechasInicioReservadas[i];
        if (!(entrada < desde) && !(hasta < entrada)) {
            char* str = entrada.toString();
            cout << "- Entrada: " << str << " | Noches: " << duracionesReservadas[i] << "\n";
            delete[] str;
        }
    }
}

// Obtener dueño
Anfitrion* Alojamiento::getAnfitrionResponsable() const {
    return dueno;
}
