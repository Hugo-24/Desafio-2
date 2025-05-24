#include "UdeAStay.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>

// Constructor
UdeAStay::UdeAStay() {
    // Inicializar capacidades y contadores
    capacidadAnfitriones       = 5;  cantidadAnfitriones       = 0;
    capacidadHuespedes         = 5;  cantidadHuespedes         = 0;
    capacidadAlojamientos      = 10; cantidadAlojamientos      = 0;
    capacidadReservasVigentes  = 10; cantidadReservasVigentes  = 0;
    capacidadReservasHistoricas = 10; cantidadReservasHistoricas = 0;

    totalIteraciones = 0;
    totalMemoria     = 0;

    // Reservar arreglos
    listaAnfitriones       = new Anfitrion*[capacidadAnfitriones];
    listaHuespedes         = new Huesped*[capacidadHuespedes];
    listaAlojamientos      = new Alojamiento*[capacidadAlojamientos];
    listaReservasVigentes  = new Reserva*[capacidadReservasVigentes];
    listaReservasHistoricas= new Reserva*[capacidadReservasHistoricas];

    // Leer fecha de la última ejecución y actualizar histórico si hace falta
    Fecha ultima = leerFechaArchivo("lastdate.txt");
    // Pide al usuario la fecha actual (valida > ultima):
    Fecha hoy;
    int d, m, a;
    do {
        std::cout << "Ingrese fecha actual (AAAA MM DD): ";
        std::cin >> a >> m >> d;
        hoy = Fecha(d,m,a);
        if (hoy<ultima) {
            std::cout << "No puede ser anterior a la última ejecución ("<< ultima.toString() << ").\n";
        }
    } while (hoy < ultima);

    // Si avanzó el día, actualiza histórico y guarda nueva fecha
    if (hoy>ultima) {
        actualizarHistorico(hoy);
        guardarFechaArchivo("lastdate.txt", hoy);
    }
    fechaCorte = hoy;

    // Cargar datos tras establecer fechaCorte
    cargarDatosDesdeArchivo();
}

// Destructor (libera todo)
UdeAStay::~UdeAStay() {
    for (int i = 0; i < cantidadReservasVigentes; i++) delete listaReservasVigentes[i];
    for (int i = 0; i < cantidadReservasHistoricas; i++) delete listaReservasHistoricas[i];
    for (int i = 0; i < cantidadAlojamientos; i++) delete listaAlojamientos[i];
    for (int i = 0; i < cantidadHuespedes; i++) delete listaHuespedes[i];
    for (int i = 0; i < cantidadAnfitriones; i++) delete listaAnfitriones[i];

    delete[] listaReservasVigentes;
    delete[] listaReservasHistoricas;
    delete[] listaAlojamientos;
    delete[] listaHuespedes;
    delete[] listaAnfitriones;
}


// Redimensionadores (idénticos a lo que ya tienes)
void UdeAStay::redimensionarAnfitriones() {
    int nuevaCap = capacidadAnfitriones * 2;
    Anfitrion** arr = new Anfitrion*[nuevaCap];
    for (int i = 0; i < cantidadAnfitriones; i++) arr[i] = listaAnfitriones[i];
    delete[] listaAnfitriones;
    listaAnfitriones = arr;
    capacidadAnfitriones = nuevaCap;
}

void UdeAStay::redimensionarHuespedes() {
    int nuevaCap = capacidadHuespedes * 2;
    Huesped** arr = new Huesped*[nuevaCap];
    for (int i = 0; i < cantidadHuespedes; i++) arr[i] = listaHuespedes[i];
    delete[] listaHuespedes;
    listaHuespedes = arr;
    capacidadHuespedes = nuevaCap;
}

void UdeAStay::redimensionarAlojamientos() {
    int nuevaCap = capacidadAlojamientos * 2;
    Alojamiento** arr = new Alojamiento*[nuevaCap];
    for (int i = 0; i < cantidadAlojamientos; i++) arr[i] = listaAlojamientos[i];
    delete[] listaAlojamientos;
    listaAlojamientos = arr;
    capacidadAlojamientos = nuevaCap;
}

void UdeAStay::redimensionarReservasVigentes() {
    int nuevaCap = capacidadReservasVigentes * 2;
    Reserva** arr = new Reserva*[nuevaCap];
    for (int i = 0; i < cantidadReservasVigentes; i++) arr[i] = listaReservasVigentes[i];
    delete[] listaReservasVigentes;
    listaReservasVigentes = arr;
    capacidadReservasVigentes = nuevaCap;
}

void UdeAStay::redimensionarReservasHistoricas() {
    int nuevaCap = capacidadReservasHistoricas * 2;
    Reserva** arr = new Reserva*[nuevaCap];
    for (int i = 0; i < cantidadReservasHistoricas; i++) arr[i] = listaReservasHistoricas[i];
    delete[] listaReservasHistoricas;
    listaReservasHistoricas = arr;
    capacidadReservasHistoricas = nuevaCap;
}

// === Manejo de archivo de fecha ===
Fecha UdeAStay::leerFechaArchivo(const char* nombreArchivo) {
    std::ifstream in(nombreArchivo);
    if (!in.is_open()) return Fecha();
    std::string s; std::getline(in,s);
    in.close();
    int aa,mm,dd;
    if (sscanf(s.c_str(), "%d-%d-%d", &aa,&mm,&dd)==3) {
        return Fecha(dd,mm,aa);
    }
    return Fecha();
}

void UdeAStay::guardarFechaArchivo(const char* nombreArchivo,
                                   const Fecha& fecha) {
    std::ofstream out(nombreArchivo);
    char buf[11];
    sprintf(buf, "%04d-%02d-%02d",
            fecha.getAnio(), fecha.getMes(), fecha.getDia());
    out << buf << "\n";
    out.close();
}

// Métodos del desafío (vacíos)

void UdeAStay::cargarDatosDesdeArchivo() {}
void UdeAStay::guardarDatosEnArchivo() {}
void UdeAStay::iniciarSesion(const char* documentoIdentidad, int tipoUsuario) {}
void UdeAStay::crearReserva(const char* docHuesped, const char* codAloj,
                            const Fecha& entrada, int duracion, int metodoPago,
                            const Fecha& fechaPago, double monto, const char* anotaciones) {}
void UdeAStay::anularReserva(const char* codigoReserva) {}
void UdeAStay::consultarReservasAnfitrion(const char* docAnfitrion,
                                          const Fecha& desde, const Fecha& hasta) {}
void UdeAStay::actualizarHistorico(const Fecha& nuevaFechaCorte) {}
void UdeAStay::medirConsumoDeRecursos() {}
int  UdeAStay::buscarHuespedIndex(const char* documento) { return -1; }
int  UdeAStay::buscarAlojamientoIndex(const char* codigo) { return -1; }
Reserva* UdeAStay::buscarReserva(const char* codigo) { return nullptr; }
