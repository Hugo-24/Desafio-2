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

// SECCIÓN 6: MANEJO DE ARCHIVOS

// Cargar anfitriones desde archivo anfitriones.txt
void UdeAStay::cargarAnfitrionesDesdeArchivo(const char* ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return;
    archivosAbiertos++;

    char linea[300];
    while (archivo.getline(linea, 300)) {
        lineasLeidas++;

        char* cod = extraerCampo(linea, 0);
        char* nombre = extraerCampo(linea, 1);
        char* doc = extraerCampo(linea, 2);
        char* strAntig = extraerCampo(linea, 3);
        char* strPunt = extraerCampo(linea, 4);

        int antig = atoi(strAntig);
        float punt = atof(strPunt);

        Anfitrion* anfitrion = new Anfitrion(nombre, antig);
        anfitrion->setPuntuacion(punt);
        anfitrion->setDocumentoIdentidad(doc);  // NUEVO MÉTODO

        if (cantidadAnfitriones == capacidadAnfitriones)
            redimensionarAnfitriones();
        listaAnfitriones[cantidadAnfitriones++] = anfitrion;

        delete[] cod; delete[] nombre; delete[] doc;
        delete[] strAntig; delete[] strPunt;
    }

    archivo.close();
}

// Cargar huéspedes desde archivo huespedes.txt
void UdeAStay::cargarHuespedesDesdeArchivo(const char* ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return;
    archivosAbiertos++;

    char linea[300];
    while (archivo.getline(linea, 300)) {
        lineasLeidas++;

        char* cod = extraerCampo(linea, 0);
        char* nombre = extraerCampo(linea, 1);
        char* doc = extraerCampo(linea, 2);
        char* strAntig = extraerCampo(linea, 3);
        char* strPunt = extraerCampo(linea, 4);

        int antig = atoi(strAntig);
        double punt = atof(strPunt);

        Huesped* huesped = new Huesped(nombre, doc, antig, punt);

        if (cantidadHuespedes == capacidadHuespedes)
            redimensionarHuespedes();
        listaHuespedes[cantidadHuespedes++] = huesped;

        delete[] cod; delete[] nombre; delete[] doc;
        delete[] strAntig; delete[] strPunt;
    }

    archivo.close();
}

// Cargar alojamientos desde archivo alojamientos.txt
void UdeAStay::cargarAlojamientosDesdeArchivo(const char* ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return;
    archivosAbiertos++;

    char linea[400];
    while (archivo.getline(linea, 400)) {
        lineasLeidas++;

        char* cod = extraerCampo(linea, 0);
        char* nombre = extraerCampo(linea, 1);
        char* dep = extraerCampo(linea, 2);
        char* mun = extraerCampo(linea, 3);
        char* dir = extraerCampo(linea, 4);
        char* strTipo = extraerCampo(linea, 5);
        char* strPrecio = extraerCampo(linea, 6);
        char* docAnfitrion = extraerCampo(linea, 7);
        char* textoAmenidades = extraerCampo(linea, 8);

        int tipo = atoi(strTipo);
        double precio = atof(strPrecio);

        Anfitrion* dueno = buscarAnfitrionPorDocumento(docAnfitrion);
        if (!dueno) {
            delete[] cod; delete[] nombre; delete[] dep; delete[] mun;
            delete[] dir; delete[] strTipo; delete[] strPrecio;
            delete[] docAnfitrion; delete[] textoAmenidades;
            continue;
        }

        Alojamiento* alojamiento = new Alojamiento(cod, nombre, dep, mun, dir, tipo, precio, dueno);
        dividirAmenidades(alojamiento, textoAmenidades);
        dueno->agregarAlojamiento(alojamiento);

        if (cantidadAlojamientos == capacidadAlojamientos)
            redimensionarAlojamientos();
        listaAlojamientos[cantidadAlojamientos++] = alojamiento;

        delete[] cod; delete[] nombre; delete[] dep; delete[] mun; delete[] dir;
        delete[] strTipo; delete[] strPrecio; delete[] docAnfitrion; delete[] textoAmenidades;
    }

    archivo.close();
}

// Cargar reservas desde archivo reservas.txt
void UdeAStay::cargarReservasDesdeArchivo(const char* ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return;
    archivosAbiertos++;

    char linea[500];
    while (archivo.getline(linea, 500)) {
        lineasLeidas++;

        char* cod = extraerCampo(linea, 0);
        char* docHuesped = extraerCampo(linea, 1);
        char* codAlojamiento = extraerCampo(linea, 2);
        char* strFechaEntrada = extraerCampo(linea, 3);
        char* strDuracion = extraerCampo(linea, 4);
        char* metodoPago = extraerCampo(linea, 5);
        char* strFechaPago = extraerCampo(linea, 6);
        char* strMonto = extraerCampo(linea, 7);
        char* anotaciones = extraerCampo(linea, 8);

        Huesped* huesped = buscarHuespedPorDocumento(docHuesped);
        Alojamiento* alojamiento = buscarAlojamientoPorCodigo(codAlojamiento);
        if (!huesped || !alojamiento) {
            delete[] cod; delete[] docHuesped; delete[] codAlojamiento;
            delete[] strFechaEntrada; delete[] strDuracion; delete[] metodoPago;
            delete[] strFechaPago; delete[] strMonto; delete[] anotaciones;
            continue;
        }

        int duracion = atoi(strDuracion);
        double monto = atof(strMonto);

        int d, m, a;
        sscanf(strFechaEntrada, "%d-%d-%d", &a, &m, &d);
        Fecha fechaEntrada(d, m, a);
        sscanf(strFechaPago, "%d-%d-%d", &a, &m, &d);
        Fecha fechaPago(d, m, a);

        Reserva* reserva = new Reserva(cod, fechaEntrada, duracion, alojamiento, huesped,
                                       metodoPago, fechaPago, monto, anotaciones);
        huesped->agregarReserva(reserva);
        alojamiento->agregarReservacion(fechaEntrada, duracion);

        if (cantidadReservasVigentes == capacidadReservasVigentes)
            redimensionarReservasVigentes();
        listaReservasVigentes[cantidadReservasVigentes++] = reserva;

        delete[] cod; delete[] docHuesped; delete[] codAlojamiento;
        delete[] strFechaEntrada; delete[] strDuracion; delete[] metodoPago;
        delete[] strFechaPago; delete[] strMonto; delete[] anotaciones;
    }

    archivo.close();
}

// Llama a los métodos anteriores con rutas predefinidas
void UdeAStay::cargarDatosDesdeArchivo() {
    cargarAnfitrionesDesdeArchivo("../datos/anfitriones.txt");
    cargarHuespedesDesdeArchivo("../datos/huespedes.txt");
    cargarAlojamientosDesdeArchivo("../datos/alojamientos.txt");
    cargarReservasDesdeArchivo("../datos/reservas.txt");
}

// SECCIÓN 7: CONSTRUCTOR Y DESTRUCTOR
// Constructor del sistema UdeAStay
UdeAStay::UdeAStay() {
    // Inicializar listas con capacidad inicial estándar
    capacidadAnfitriones = 5;
    cantidadAnfitriones = 0;
    listaAnfitriones = new Anfitrion*[capacidadAnfitriones];

    capacidadHuespedes = 5;
    cantidadHuespedes = 0;
    listaHuespedes = new Huesped*[capacidadHuespedes];

    capacidadAlojamientos = 5;
    cantidadAlojamientos = 0;
    listaAlojamientos = new Alojamiento*[capacidadAlojamientos];

    capacidadReservasVigentes = 10;
    cantidadReservasVigentes = 0;
    listaReservasVigentes = new Reserva*[capacidadReservasVigentes];

    capacidadReservasHistoricas = 10;
    cantidadReservasHistoricas = 0;
    listaReservasHistoricas = new Reserva*[capacidadReservasHistoricas];

    // Fecha de corte inicial (puede cambiar al cargar)
    fechaCorte = Fecha(1, 1, 2025);

    // Inicializar contadores de recursos
    totalIteraciones = 0;
    totalMemoria = 0;
    archivosAbiertos = 0;
    lineasLeidas = 0;
}

// Destructor: libera memoria de todas las listas dinámicas
UdeAStay::~UdeAStay() {
    for (int i = 0; i < cantidadAnfitriones; i++) {
        delete listaAnfitriones[i];
    }
    delete[] listaAnfitriones;

    for (int i = 0; i < cantidadHuespedes; i++) {
        delete listaHuespedes[i];
    }
    delete[] listaHuespedes;

    for (int i = 0; i < cantidadAlojamientos; i++) {
        delete listaAlojamientos[i];
    }
    delete[] listaAlojamientos;

    for (int i = 0; i < cantidadReservasVigentes; i++) {
        delete listaReservasVigentes[i];
    }
    delete[] listaReservasVigentes;

    for (int i = 0; i < cantidadReservasHistoricas; i++) {
        delete listaReservasHistoricas[i];
    }
    delete[] listaReservasHistoricas;
}

// SECCIÓN 8: FUNCIONALIDADES PRINCIPALES

// Permite iniciar sesión como huésped (1) o anfitrión (0)
void UdeAStay::iniciarSesion(const char* documentoIdentidad, int tipoUsuario) {
    if (tipoUsuario == 1) {
        Huesped* h = buscarHuespedPorDocumento(documentoIdentidad);
        if (h) {
            h->imprimirResumen();
        } else {
            cout << "Huesped no encontrado.\n";
        }
    } else {
        Anfitrion* a = buscarAnfitrionPorDocumento(documentoIdentidad);
        if (a) {
            char* nombre = a->getNombreCompleto();
            cout << "Bienvenido, " << nombre << ".\n";
            delete[] nombre;
        } else {
            cout << "Anfitrion no encontrado.\n";
        }
    }
}

// Crea una nueva reserva si el huésped y alojamiento existen y hay disponibilidad
void UdeAStay::crearReserva(const char* documentoHuesped,
                            const char* codigoAlojamiento,
                            const Fecha& fechaEntrada,
                            int duracion,
                            int metodoPago,
                            const Fecha& fechaPago,
                            double monto,
                            const char* anotaciones) {
    Huesped* huesped = buscarHuespedPorDocumento(documentoHuesped);
    Alojamiento* alojamiento = buscarAlojamientoPorCodigo(codigoAlojamiento);

    if (!huesped || !alojamiento) {
        cout << "Error: huesped o alojamiento no encontrado.\n";
        return;
    }

    if (!validarDisponibilidad(alojamiento, fechaEntrada, duracion)) {
        cout << "El alojamiento no esta disponible para esas fechas.\n";
        return;
    }

    // Validar que el huésped no tenga conflicto de fechas
    Fecha finNueva = fechaEntrada + duracion;
    for (int i = 0; i < huesped->getCantidadReservas(); i++) {
        Reserva* r = huesped->getReserva(i);
        Fecha entrada = r->getFechaEntrada();
        Fecha salida = r->calcularFechaSalida();
        if (!(finNueva <= entrada || salida <= fechaEntrada)) {
            cout << "El huesped ya tiene una reserva que se solapa.\n";
            return;
        }
        totalIteraciones++;
    }

    // Convertir método de pago
    const char* metodo = metodoPago == 0 ? "PSE" : "TCredito";

    // Crear reserva
    Reserva* nueva = new Reserva(fechaEntrada, duracion, alojamiento, huesped,
                                 metodo, fechaPago, monto, anotaciones);

    huesped->agregarReserva(nueva);
    alojamiento->agregarReservacion(fechaEntrada, duracion);

    if (cantidadReservasVigentes == capacidadReservasVigentes)
        redimensionarReservasVigentes();
    listaReservasVigentes[cantidadReservasVigentes++] = nueva;

    nueva->mostrarComprobante();
}

// Anula una reserva según su código
void UdeAStay::anularReserva(const char* codigoReserva) {
    // Buscar y eliminar en vigentes
    for (int i = 0; i < cantidadReservasVigentes; i++) {
        totalIteraciones++;
        if (sonIguales(listaReservasVigentes[i]->getCodigo(), codigoReserva)) {
            Huesped* h = listaReservasVigentes[i]->getHuesped();
            Alojamiento* a = listaReservasVigentes[i]->getAlojamiento();

            if (h) h->anularReservacion(codigoReserva);
            if (a) a->eliminarReservacion(codigoReserva);

            delete listaReservasVigentes[i];

            for (int j = i; j < cantidadReservasVigentes - 1; j++) {
                listaReservasVigentes[j] = listaReservasVigentes[j + 1];
            }

            cantidadReservasVigentes--;
            cout << "Reserva anulada exitosamente.\n";
            return;
        }
    }

    cout << "Reserva no encontrada o ya es historica.\n";
}

// Permite a un anfitrión ver reservas en un rango de fechas
void UdeAStay::consultarReservasAnfitrion(const char* documentoAnfitrion, const Fecha& desde, const Fecha& hasta) {
    Anfitrion* anfitrion = buscarAnfitrionPorDocumento(documentoAnfitrion);
    if (!anfitrion) {
        cout << "Anfitrion no encontrado.\n";
        return;
    }
    anfitrion->verReservaciones(desde, hasta);
}

// Mueve reservas anteriores a la fecha de corte al histórico
void UdeAStay::actualizarHistorico(const Fecha& nuevaFechaCorte) {
    int i = 0;
    while (i < cantidadReservasVigentes) {
        Reserva* r = listaReservasVigentes[i];
        Fecha salida = r->calcularFechaSalida();
        if (salida < nuevaFechaCorte) {
            if (cantidadReservasHistoricas == capacidadReservasHistoricas)
                redimensionarReservasHistoricas();

            listaReservasHistoricas[cantidadReservasHistoricas++] = r;

            for (int j = i; j < cantidadReservasVigentes - 1; j++) {
                listaReservasVigentes[j] = listaReservasVigentes[j + 1];
            }

            cantidadReservasVigentes--;
        } else {
            i++;
        }
        totalIteraciones++;
    }

    fechaCorte = nuevaFechaCorte;
    cout << "Historico actualizado a partir del ";
    char* txt = fechaCorte.toString();
    cout << txt << ".\n";
    delete[] txt;
}

// Muestra métricas de consumo de recursos
void UdeAStay::medirConsumoDeRecursos() {
    cout << ">>> CONSUMO DE RECURSOS <<<\n";
    cout << "Iteraciones totales: " << totalIteraciones << "\n";
    cout << "Memoria dinámica (estimada): " << totalMemoria << " bytes\n";
    cout << "Archivos abiertos: " << archivosAbiertos << "\n";
    cout << "Líneas leídas desde archivos: " << lineasLeidas << "\n";
    cout << "-----------------------------\n";
}
