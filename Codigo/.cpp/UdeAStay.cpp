#include "UdeAStay.h"
#include <fstream>  // Para manejo de archivos
#include <iostream>
using namespace std;

// SECCIÓN 1: ESTRUCTURAS INTERNAS

// Devuelve la cantidad actual de huéspedes registrados
int UdeAStay::getCantidadHuespedes() const {
    return cantidadHuespedes;
}

// Devuelve la cantidad actual de anfitriones registrados
int UdeAStay::getCantidadAnfitriones() const {
    return cantidadAnfitriones;
}

// Devuelve la cantidad actual de alojamientos registrados
int UdeAStay::getCantidadAlojamientos() const {
    return cantidadAlojamientos;
}

// Devuelve la cantidad de reservas que aún están vigentes
int UdeAStay::getCantidadReservasVigentes() const {
    return cantidadReservasVigentes;
}

// Devuelve la cantidad de reservas ya históricas
int UdeAStay::getCantidadReservasHistoricas() const {
    return cantidadReservasHistoricas;
}

// Muestra un resumen completo del estado del sistema
void UdeAStay::mostrarResumenDatos() const {
    cout << "===== RESUMEN DEL SISTEMA UdeAStay =====" << endl;
    cout << "Fecha de corte del sistema: ";
    char* fechaTexto = fechaCorte.toString();
    cout << fechaTexto << endl;
    delete[] fechaTexto;

    cout << "Cantidad de anfitriones registrados: " << cantidadAnfitriones << endl;
    cout << "Cantidad de huespedes registrados:   " << cantidadHuespedes << endl;
    cout << "Cantidad de alojamientos cargados:  " << cantidadAlojamientos << endl;
    cout << "Reservas vigentes:                  " << cantidadReservasVigentes << endl;
    cout << "Reservas historicas:               " << cantidadReservasHistoricas << endl;
    cout << "========================================" << endl;
}

// SECCIÓN 2: REDIMENSIONAMIENTO

// Redimensiona la lista de punteros a anfitriones
void UdeAStay::redimensionarAnfitriones() {
    int nuevaCapacidad = capacidadAnfitriones * 2;
    Anfitrion** nuevaLista = new Anfitrion*[nuevaCapacidad];

    for (int i = 0; i < cantidadAnfitriones; i++) {
        nuevaLista[i] = listaAnfitriones[i];
        totalIteraciones++;
    }

    delete[] listaAnfitriones;
    listaAnfitriones = nuevaLista;
    capacidadAnfitriones = nuevaCapacidad;

    totalMemoria += sizeof(Anfitrion*) * nuevaCapacidad;
}

// Redimensiona la lista de punteros a huéspedes
void UdeAStay::redimensionarHuespedes() {
    int nuevaCapacidad = capacidadHuespedes * 2;
    Huesped** nuevaLista = new Huesped*[nuevaCapacidad];

    for (int i = 0; i < cantidadHuespedes; i++) {
        nuevaLista[i] = listaHuespedes[i];
        totalIteraciones++;
    }

    delete[] listaHuespedes;
    listaHuespedes = nuevaLista;
    capacidadHuespedes = nuevaCapacidad;

    totalMemoria += sizeof(Huesped*) * nuevaCapacidad;
}

// Redimensiona la lista de punteros a alojamientos
void UdeAStay::redimensionarAlojamientos() {
    int nuevaCapacidad = capacidadAlojamientos * 2;
    Alojamiento** nuevaLista = new Alojamiento*[nuevaCapacidad];

    for (int i = 0; i < cantidadAlojamientos; i++) {
        nuevaLista[i] = listaAlojamientos[i];
        totalIteraciones++;
    }

    delete[] listaAlojamientos;
    listaAlojamientos = nuevaLista;
    capacidadAlojamientos = nuevaCapacidad;

    totalMemoria += sizeof(Alojamiento*) * nuevaCapacidad;
}

// Redimensiona la lista de reservas vigentes
void UdeAStay::redimensionarReservasVigentes() {
    int nuevaCapacidad = capacidadReservasVigentes * 2;
    Reserva** nuevaLista = new Reserva*[nuevaCapacidad];

    for (int i = 0; i < cantidadReservasVigentes; i++) {
        nuevaLista[i] = listaReservasVigentes[i];
        totalIteraciones++;
    }

    delete[] listaReservasVigentes;
    listaReservasVigentes = nuevaLista;
    capacidadReservasVigentes = nuevaCapacidad;

    totalMemoria += sizeof(Reserva*) * nuevaCapacidad;
}

// Redimensiona la lista de reservas históricas
void UdeAStay::redimensionarReservasHistoricas() {
    int nuevaCapacidad = capacidadReservasHistoricas * 2;
    Reserva** nuevaLista = new Reserva*[nuevaCapacidad];

    for (int i = 0; i < cantidadReservasHistoricas; i++) {
        nuevaLista[i] = listaReservasHistoricas[i];
        totalIteraciones++;
    }

    delete[] listaReservasHistoricas;
    listaReservasHistoricas = nuevaLista;
    capacidadReservasHistoricas = nuevaCapacidad;

    totalMemoria += sizeof(Reserva*) * nuevaCapacidad;
}
// SECCIÓN 3: FUNCIONES DE BÚSQUEDA

// Busca un huésped por documento y retorna el puntero si lo encuentra
Huesped* UdeAStay::buscarHuespedPorDocumento(const char* documento) {
    for (int i = 0; i < cantidadHuespedes; i++) {
        totalIteraciones++;
        const char* doc = listaHuespedes[i]->getDocumentoIdentidad();
        bool iguales = sonIguales(doc, documento);
        delete[] doc;
        if (iguales) return listaHuespedes[i];
    }
    return nullptr;
}

// Busca un anfitrión por documento y retorna el puntero si lo encuentra
Anfitrion* UdeAStay::buscarAnfitrionPorDocumento(const char* documento) {
    for (int i = 0; i < cantidadAnfitriones; i++) {
        totalIteraciones++;
        const char* doc = listaAnfitriones[i]->getDocumentoIdentidad();
        bool iguales = sonIguales(doc, documento);
        delete[] doc;
        if (iguales) return listaAnfitriones[i];
    }
    return nullptr;
}

// Busca un alojamiento por código y retorna el puntero si lo encuentra
Alojamiento* UdeAStay::buscarAlojamientoPorCodigo(const char* codigo) {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        totalIteraciones++;
        const char* cod = listaAlojamientos[i]->getCodigo();
        bool iguales = sonIguales(cod, codigo);
        delete[] cod;
        if (iguales) return listaAlojamientos[i];
    }
    return nullptr;
}

// Busca una reserva vigente o histórica por su código
Reserva* UdeAStay::buscarReserva(const char* codigo) {
    // Buscar primero en reservas vigentes
    for (int i = 0; i < cantidadReservasVigentes; i++) {
        totalIteraciones++;
        const char* cod = listaReservasVigentes[i]->getCodigo();
        bool iguales = sonIguales(cod, codigo);
        delete[] cod;
        if (iguales) return listaReservasVigentes[i];
    }

    // Si no está vigente, buscar en el histórico
    for (int i = 0; i < cantidadReservasHistoricas; i++) {
        totalIteraciones++;
        const char* cod = listaReservasHistoricas[i]->getCodigo();
        bool iguales = sonIguales(cod, codigo);
        delete[] cod;
        if (iguales) return listaReservasHistoricas[i];
    }

    return nullptr; // No se encontró
}

// Busca la posición de un huésped en la lista (útil para pruebas)
int UdeAStay::buscarHuespedIndex(const char* documento) {
    for (int i = 0; i < cantidadHuespedes; i++) {
        totalIteraciones++;
        const char* doc = listaHuespedes[i]->getDocumentoIdentidad();
        bool iguales = sonIguales(doc, documento);
        delete[] doc;
        if (iguales) return i;
    }
    return -1;
}

// Busca la posición de un alojamiento en la lista
int UdeAStay::buscarAlojamientoIndex(const char* codigo) {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        totalIteraciones++;
        const char* cod = listaAlojamientos[i]->getCodigo();
        bool iguales = sonIguales(cod, codigo);
        delete[] cod;
        if (iguales) return i;
    }
    return -1;
}

// SECCIÓN 4: MANEJO DE TEXTO
// Crea una copia dinámica del texto recibido
char* UdeAStay::copiarTexto(const char* textoOriginal) {
    if (!textoOriginal) return nullptr;

    int longitud = 0;
    while (textoOriginal[longitud] != '\0') {
        longitud++;
        totalIteraciones++;
    }

    char* copia = new char[longitud + 1];
    totalMemoria += (longitud + 1) * sizeof(char);

    for (int i = 0; i <= longitud; i++) {
        copia[i] = textoOriginal[i];
        totalIteraciones++;
    }

    return copia;
}

// Compara dos cadenas carácter por carácter
bool UdeAStay::sonIguales(const char* texto1, const char* texto2) {
    if (!texto1 || !texto2) return false;

    int i = 0;
    while (texto1[i] != '\0' && texto2[i] != '\0') {
        totalIteraciones++;
        if (texto1[i] != texto2[i]) return false;
        i++;
    }

    return texto1[i] == texto2[i]; // Ambos deben terminar al mismo tiempo
}

// SECCIÓN 5: FUNCIONES AUXILIARES

// Verifica si un alojamiento está disponible para todo el rango de la reserva
bool UdeAStay::validarDisponibilidad(Alojamiento* alojamiento, const Fecha& inicio, int duracion) {
    if (!alojamiento) return false;

    Fecha actual = inicio;
    for (int i = 0; i < duracion; i++) {
        if (!alojamiento->estaDisponible(actual)) {
            return false;
        }
        actual = actual + 1;
        totalIteraciones++;
    }
    return true;
}

// Extrae el campo número `indice` de una línea separada por `;`
char* UdeAStay::extraerCampo(const char* linea, int indice) {
    if (!linea) return nullptr;

    int actual = 0;
    int inicio = 0;
    int i = 0;

    while (linea[i] != '\0') {
        if (actual == indice) break;
        if (linea[i] == ';') {
            actual++;
            inicio = i + 1;
        }
        i++;
        totalIteraciones++;
    }

    int fin = inicio;
    while (linea[fin] != '\0' && linea[fin] != ';') {
        fin++;
        totalIteraciones++;
    }

    int longitud = fin - inicio;
    char* campo = new char[longitud + 1];
    totalMemoria += (longitud + 1) * sizeof(char);

    for (int j = 0; j < longitud; j++) {
        campo[j] = linea[inicio + j];
        totalIteraciones++;
    }
    campo[longitud] = '\0';

    return campo;
}

// Cuenta la cantidad de campos en una línea de texto separados por `;`
int UdeAStay::contarCampos(const char* linea) {
    if (!linea) return 0;

    int contador = 1; // Al menos un campo
    for (int i = 0; linea[i] != '\0'; i++) {
        if (linea[i] == ';') contador++;
        totalIteraciones++;
    }
    return contador;
}

// Convierte un texto tipo "wifi,piscina,patio" en bits de amenidades activas
void UdeAStay::dividirAmenidades(Alojamiento* alojamiento, const char* texto) {
    if (!alojamiento || !texto) return;

    // Lista fija de amenidades conocidas
    const char* amenidadesConocidas[] = {
        "wifi", "piscina", "aire", "caja", "parqueadero", "patio", "cocina"
    };
    const int totalAmenidades = 7;

    int i = 0, inicio = 0;
    while (true) {
        // Detectar fin de palabra
        if (texto[i] == ',' || texto[i] == '\0') {
            int longitud = i - inicio;
            char* palabra = new char[longitud + 1];
            totalMemoria += (longitud + 1) * sizeof(char);

            for (int j = 0; j < longitud; j++) {
                palabra[j] = texto[inicio + j];
                totalIteraciones++;
            }
            palabra[longitud] = '\0';

            // Buscar coincidencia
            for (int k = 0; k < totalAmenidades; k++) {
                if (sonIguales(palabra, amenidadesConocidas[k])) {
                    alojamiento->agregarAmenidad(k);
                    break;
                }
            }

            delete[] palabra;
            inicio = i + 1;
        }

        if (texto[i] == '\0') break;
        i++;
    }
}
