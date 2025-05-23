#include "Alojamiento.h"
#include "Anfitrion.h"
#include <iostream>

using namespace std;

// Inicialización de contadores
int Alojamiento::totalAlojamientosCreados = 0;
int Alojamiento::totalIteracionesEnReservas = 0;

// Función para calcular la longitud de un texto sin usar <cstring>
int Alojamiento::longitudTexto(const char* texto) const {
    int i = 0;
    while (texto[i] != '\0') {
        i++;
    }
    return i;
}

// Copia manual de texto (como strcpy pero hecho a mano)
void Alojamiento::copiarTextoManual(char* destino, const char* fuente) const {
    int i = 0;
    while (fuente[i] != '\0') {
        destino[i] = fuente[i];
        i++;
    }
    destino[i] = '\0';
}

// Crea una nueva copia dinámica de un texto
char* Alojamiento::copiarTexto(const char* texto) const {
    int longitud = longitudTexto(texto);
    char* copia = new char[longitud + 1];
    copiarTextoManual(copia, texto);
    return copia;
}

// Duplica el tamaño de los arreglos de reservas si se llenan
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

    totalAlojamientosCreados++;
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

    totalAlojamientosCreados++;
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

// Amenidades (bitmask)
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

// Verifica si hay una reserva con esa fecha exacta
bool Alojamiento::estaDisponible(const Fecha& inicio) const {
    for (int i = 0; i < cantidadReservaciones; i++) {
        totalIteracionesEnReservas++;
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

// Eliminar reserva (simulado)
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
        totalIteracionesEnReservas++;
        const Fecha& entrada = fechasInicioReservadas[i];
        if (!(entrada < desde) && !(hasta < entrada)) {
            char* str = entrada.toString();
            cout << "- Entrada: " << str << " | Noches: " << duracionesReservadas[i] << "\n";
            delete[] str;
        }
    }
}

// Devolver puntero al anfitrión dueño
Anfitrion* Alojamiento::getAnfitrionResponsable() const {
    return dueno;
}

// Getters de los contadores
int Alojamiento::getTotalAlojamientosCreados() {
    return totalAlojamientosCreados;
}

int Alojamiento::getTotalIteraciones() {
    return totalIteracionesEnReservas;
}
