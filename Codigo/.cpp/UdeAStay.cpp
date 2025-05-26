#include "UdeAStay.h"
#include "Funciones.h"
#include <fstream>  // Solo para manejo de archivos de texto
#include <iostream>

using namespace std;

// SECCIÓN 1: ESTRUCTURAS INTERNAS
// Métodos básicos de consulta y resumen

// Devuelve la cantidad de huéspedes registrados
int UdeAStay::getCantidadHuespedes() const {
    return cantidadHuespedes;
}

// Devuelve la cantidad de anfitriones registrados
int UdeAStay::getCantidadAnfitriones() const {
    return cantidadAnfitriones;
}

// Devuelve la cantidad de alojamientos registrados
int UdeAStay::getCantidadAlojamientos() const {
    return cantidadAlojamientos;
}

// Devuelve la cantidad de reservas vigentes activas
int UdeAStay::getCantidadReservasVigentes() const {
    return cantidadReservasVigentes;
}

// Devuelve la cantidad de reservas históricas registradas
int UdeAStay::getCantidadReservasHistoricas() const {
    return cantidadReservasHistoricas;
}

// Muestra un resumen general del estado actual del sistema
void UdeAStay::mostrarResumenDatos() const {
    char* textoFecha = fechaCorte.toString();

    // Salida organizada de datos del sistema
    cout << "===== ESTADO ACTUAL DE UdeAStay =====" << endl;
    cout << "Fecha de corte del sistema: " << textoFecha << endl;
    cout << "-------------------------------------" << endl;
    cout << "Anfitriones registrados:    " << cantidadAnfitriones << endl;
    cout << "Huespedes registrados:      " << cantidadHuespedes << endl;
    cout << "Alojamientos disponibles:   " << cantidadAlojamientos << endl;
    cout << "Reservas vigentes:          " << cantidadReservasVigentes << endl;
    cout << "Reservas historicas:        " << cantidadReservasHistoricas << endl;
    cout << "=====================================" << endl;

    delete[] textoFecha;
}

// SECCIÓN 2: REDIMENSIONAMIENTO DE LISTAS DINÁMICAS

// Redimensiona la lista de anfitriones al doble de capacidad
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

    totalMemoria += nuevaCapacidad * sizeof(Anfitrion*);
}

// Redimensiona la lista de huéspedes
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

    totalMemoria += nuevaCapacidad * sizeof(Huesped*);
}

// Redimensiona la lista de alojamientos
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

    totalMemoria += nuevaCapacidad * sizeof(Alojamiento*);
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

    totalMemoria += nuevaCapacidad * sizeof(Reserva*);
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

    totalMemoria += nuevaCapacidad * sizeof(Reserva*);
}

// SECCIÓN 3: FUNCIONES DE BÚSQUEDA EN LISTAS INTERNAS

// Busca un huésped según su documento de identidad
Huesped* UdeAStay::buscarHuespedPorDocumento(const char* documento) {
    for (int i = 0; i < cantidadHuespedes; i++) {
        const char* doc = listaHuespedes[i]->getDocumentoIdentidad();
        totalIteraciones++;
        if (sonIguales(doc, documento)) {
            return listaHuespedes[i];
        }
    }
    return nullptr;
}

// Busca un anfitrión por su documento de identidad
Anfitrion* UdeAStay::buscarAnfitrionPorDocumento(const char* documento) {
    for (int i = 0; i < cantidadAnfitriones; i++) {
        const char* doc = listaAnfitriones[i]->getDocumentoIdentidad();
        totalIteraciones++;
        if (sonIguales(doc, documento)) {
            return listaAnfitriones[i];
        }
    }
    return nullptr;
}

// Busca un alojamiento según su código único (ej. ALO-0001)
Alojamiento* UdeAStay::buscarAlojamientoPorCodigo(const char* codigo) {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        const char* cod = listaAlojamientos[i]->getCodigo();
        totalIteraciones++;
        if (sonIguales(cod, codigo)) {
            return listaAlojamientos[i];
        }
    }
    return nullptr;
}

// Busca el índice (posición) de un huésped en la lista
int UdeAStay::buscarHuespedIndex(const char* documento) {
    for (int i = 0; i < cantidadHuespedes; i++) {
        totalIteraciones++;
        if (sonIguales(listaHuespedes[i]->getDocumentoIdentidad(), documento)) {
            return i;
        }
    }
    return -1;
}

// Busca el índice de un alojamiento en la lista
int UdeAStay::buscarAlojamientoIndex(const char* codigo) {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        totalIteraciones++;
        if (sonIguales(listaAlojamientos[i]->getCodigo(), codigo)) {
            return i;
        }
    }
    return -1;
}

// Busca una reserva por su código único (primero en vigentes, luego en históricas)
Reserva* UdeAStay::buscarReserva(const char* codigo) {
    for (int i = 0; i < cantidadReservasVigentes; i++) {
        totalIteraciones++;
        if (sonIguales(listaReservasVigentes[i]->getCodigo(), codigo)) {
            return listaReservasVigentes[i];
        }
    }
    for (int i = 0; i < cantidadReservasHistoricas; i++) {
        totalIteraciones++;
        if (sonIguales(listaReservasHistoricas[i]->getCodigo(), codigo)) {
            return listaReservasHistoricas[i];
        }
    }
    return nullptr;
}

// SECCIÓN 4: MANEJO DE TEXTO MANUAL
//...

// SECCIÓN 5: FUNCIONES AUXILIARES
// Verifica si un alojamiento está disponible para todas las noches de una reserva
bool UdeAStay::validarDisponibilidad(Alojamiento* alojamiento, const Fecha& inicio, int duracion) {
    if (!alojamiento) return false;

    Fecha actual = inicio;
    for (int i = 0; i < duracion; i++) {
        if (!alojamiento->estaDisponible(actual)) return false;
        actual = actual + 1;
        totalIteraciones++;
    }
    return true;
}

// Extrae el campo en la posición `indice` de una línea separada por `;`
char* UdeAStay::extraerCampo(const char* linea, int indice) {
    if (!linea) return nullptr;

    int actual = 0, inicio = 0, i = 0;

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

// Cuenta cuántos campos hay en una línea separados por `;`
int UdeAStay::contarCampos(const char* linea) {
    if (!linea || linea[0] == '\0') return 0;

    int contador = 1;
    for (int i = 0; linea[i] != '\0'; i++) {
        if (linea[i] == ';') contador++;
        totalIteraciones++;
    }
    return contador;
}

// Convierte una cadena tipo "wifi,piscina,cocina" en flags de amenidades para un alojamiento
void UdeAStay::dividirAmenidades(Alojamiento* alojamiento, const char* texto) {
    if (!alojamiento || !texto) return;

    const char* amenidadesConocidas[] = {
        "wifi", "piscina", "aire", "caja", "parqueadero", "patio", "cocina"
    };
    const int totalAmenidades = 7;

    int i = 0, inicio = 0;
    while (true) {
        if (texto[i] == ',' || texto[i] == '\0') {
            int longitud = i - inicio;
            char* palabra = new char[longitud + 1];
            totalMemoria += (longitud + 1) * sizeof(char);

            for (int j = 0; j < longitud; j++) {
                palabra[j] = texto[inicio + j];
                totalIteraciones++;
            }
            palabra[longitud] = '\0';

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

// Compara dos fechas y determina si la nuevaFecha es posterior a fechaExistente
bool UdeAStay::esFechaPosterior(const Fecha& nuevaFecha, const Fecha& fechaExistente) {
    return fechaExistente < nuevaFecha;
}

// Lee una fecha en formato "dd-mm-aaaa" desde archivo (línea única)
Fecha UdeAStay::leerFechaMasRecienteDelHistorico(const char* ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return Fecha(1, 1, 2000);

    archivosAbiertos++;
    lineasLeidas++;

    char buffer[30];
    archivo.getline(buffer, 30);
    archivo.close();

    int d, m, a;
    sscanf(buffer, "%d-%d-%d", &d, &m, &a);
    return Fecha(d, m, a);
}

// SECCIÓN 6: MANEJO DE ARCHIVOS
// ---------- CARGA DE DATOS DESDE ARCHIVOS .TXT ----------

// Carga anfitriones desde archivo con formato: documento;nombre;antiguedad;puntuacion
void UdeAStay::cargarAnfitriones(const char* ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return;

    archivosAbiertos++;
    char linea[1024];

    while (archivo.getline(linea, 1024)) {
        lineasLeidas++;

        char* documento = extraerCampo(linea, 0);
        char* nombre = extraerCampo(linea, 1);
        char* textoAntiguedad = extraerCampo(linea, 2);
        char* textoPuntuacion = extraerCampo(linea, 3);

        int antiguedad = convertirEntero(textoAntiguedad);
        double puntuacion = convertirDouble(textoPuntuacion);

        if (cantidadAnfitriones == capacidadAnfitriones)
            redimensionarAnfitriones();

        Anfitrion* nuevo = new Anfitrion(nombre, antiguedad);
        nuevo->setDocumentoIdentidad(documento);
        nuevo->setPuntuacion((float)puntuacion);

        listaAnfitriones[cantidadAnfitriones++] = nuevo;
        totalMemoria += sizeof(Anfitrion);

        delete[] documento;
        delete[] nombre;
        delete[] textoAntiguedad;
        delete[] textoPuntuacion;
    }

    archivo.close();
}

// Carga huéspedes desde archivo con formato: documento;nombre;antiguedad;puntuacion
void UdeAStay::cargarHuespedes(const char* ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return;

    archivosAbiertos++;
    char linea[1024];

    while (archivo.getline(linea, 1024)) {
        lineasLeidas++;

        char* documento = extraerCampo(linea, 0);
        char* nombre = extraerCampo(linea, 1);
        char* textoAntiguedad = extraerCampo(linea, 2);
        char* textoPuntuacion = extraerCampo(linea, 3);

        int antiguedad = convertirEntero(textoAntiguedad);
        double puntuacion = convertirDouble(textoPuntuacion);

        if (cantidadHuespedes == capacidadHuespedes)
            redimensionarHuespedes();

        Huesped* nuevo = new Huesped(nombre, documento, antiguedad, puntuacion);
        listaHuespedes[cantidadHuespedes++] = nuevo;
        totalMemoria += sizeof(Huesped);

        delete[] documento;
        delete[] nombre;
        delete[] textoAntiguedad;
        delete[] textoPuntuacion;
    }

    archivo.close();
}

// Carga alojamientos desde archivo con formato:
// codigo;nombre;departamento;municipio;direccion;tipo;precio;documentoDueno;amenidades
void UdeAStay::cargarAlojamientos(const char* ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return;

    archivosAbiertos++;
    char linea[1024];

    while (archivo.getline(linea, 1024)) {
        lineasLeidas++;

        // Extraemos todos los campos uno por uno
        char* codigo = extraerCampo(linea, 0);
        char* nombre = extraerCampo(linea, 1);
        char* departamento = extraerCampo(linea, 2);
        char* municipio = extraerCampo(linea, 3);
        char* direccion = extraerCampo(linea, 4);
        char* textoTipo = extraerCampo(linea, 5);
        char* textoPrecio = extraerCampo(linea, 6);
        char* documentoDueno = extraerCampo(linea, 7);
        char* textoAmenidades = extraerCampo(linea, 8);

        int tipo = convertirEntero(textoTipo);
        double precio = convertirDouble(textoPrecio);

        // Buscamos al dueño del alojamiento
        Anfitrion* dueno = buscarAnfitrionPorDocumento(documentoDueno);
        if (!dueno) {
            // Si el dueño no existe, liberamos todo y saltamos esta línea
            delete[] codigo; delete[] nombre; delete[] departamento;
            delete[] municipio; delete[] direccion; delete[] textoTipo;
            delete[] textoPrecio; delete[] documentoDueno; delete[] textoAmenidades;
            continue;
        }

        // Redimensionar si no hay espacio en el arreglo
        if (cantidadAlojamientos == capacidadAlojamientos)
            redimensionarAlojamientos();

        // Creamos el alojamiento y lo vinculamos al dueño
        Alojamiento* nuevo = new Alojamiento(codigo, nombre, departamento, municipio,
                                             direccion, tipo, precio, dueno);
        dividirAmenidades(nuevo, textoAmenidades); // Cargamos sus amenidades
        dueno->agregarAlojamiento(nuevo);           // Lo agregamos al anfitrión
        listaAlojamientos[cantidadAlojamientos++] = nuevo;

        totalMemoria += sizeof(Alojamiento);

        // Liberamos todos los campos temporales
        delete[] codigo;
        delete[] nombre;
        delete[] departamento;
        delete[] municipio;
        delete[] direccion;
        delete[] textoTipo;
        delete[] textoPrecio;
        delete[] documentoDueno;
        delete[] textoAmenidades;
    }

    archivo.close();
}

// Carga reservas vigentes desde archivo con campos separados por ';'
void UdeAStay::cargarReservasVigentes(const char* ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return;

    archivosAbiertos++;
    char linea[2048];

    while (archivo.getline(linea, 2048)) {
        lineasLeidas++;
        crearReservaDesdeTexto(linea);

        if (cantidadReservasVigentes == capacidadReservasVigentes)
            redimensionarReservasVigentes();
    }

    archivo.close();
}

// Carga reservas históricas desde archivo (mismo formato que reservas vigentes)
void UdeAStay::cargarReservasHistoricas(const char* ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return;

    archivosAbiertos++;
    char linea[2048];

    while (archivo.getline(linea, 2048)) {
        lineasLeidas++;

        // Creamos la reserva y la agregamos a la lista histórica
        crearReservaDesdeTexto(linea);

        if (cantidadReservasHistoricas == capacidadReservasHistoricas)
            redimensionarReservasHistoricas();
    }

    archivo.close();
}

// Carga la fecha de corte desde un archivo simple con una sola línea: dd-mm-aaaa
void UdeAStay::cargarFechaCorte(const char* ruta) {
    fechaCorte = leerFechaMasRecienteDelHistorico(ruta);
}

// ---------- GUARDADO DE DATOS EN ARCHIVOS .TXT ----------
// Guarda todos los anfitriones en un archivo de texto.
// Formato por línea: documento;nombre;antiguedad;puntuacion
void UdeAStay::guardarAnfitriones(const char* ruta) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) return;

    archivosAbiertos++;
    for (int i = 0; i < cantidadAnfitriones; i++) {
        Anfitrion* a = listaAnfitriones[i];
        archivo << a->getDocumentoIdentidad() << ";"
                << a->getNombreCompleto() << ";"
                << a->getAntiguedadEnMeses() << ";"
                << a->getPuntuacion() << "\n";
        totalIteraciones++;
    }

    archivo.close();
}
// Guarda todos los huéspedes en un archivo de texto.
// Formato por línea: documento;nombre;antiguedad;puntuacion
void UdeAStay::guardarHuespedes(const char* ruta) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) return;

    archivosAbiertos++;
    for (int i = 0; i < cantidadHuespedes; i++) {
        Huesped* h = listaHuespedes[i];
        archivo << h->getDocumentoIdentidad() << ";"
                << h->getNombreCompleto() << ";"
                << h->getAntiguedadEnMeses() << ";"
                << h->getPuntuacionPromedio() << "\n";
        totalIteraciones++;
    }

    archivo.close();
}
// Guarda todos los alojamientos en un archivo de texto.
// Formato: codigo;nombre;departamento;municipio;direccion;tipo;precio;documentoDueno;amenidades
void UdeAStay::guardarAlojamientos(const char* ruta) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) return;

    archivosAbiertos++;
    for (int i = 0; i < cantidadAlojamientos; i++) {
        Alojamiento* a = listaAlojamientos[i];

        archivo << a->getCodigo() << ";"
                << a->getNombre() << ";"
                << a->getDepartamento() << ";"
                << a->getMunicipio() << ";"
                << a->getDireccion() << ";"
                << a->getTipoAlojamiento() << ";"
                << a->getPrecioPorNoche() << ";"
                << a->getAnfitrionResponsable()->getDocumentoIdentidad() << ";";

        // Amenidades codificadas en texto (ej: wifi,parqueadero,cocina)
        bool primera = true;
        if (a->tieneAmenidad(0)) { archivo << "wifi"; primera = false; }
        if (a->tieneAmenidad(1)) { if (!primera) archivo << ","; archivo << "piscina"; primera = false; }
        if (a->tieneAmenidad(2)) { if (!primera) archivo << ","; archivo << "aire"; primera = false; }
        if (a->tieneAmenidad(3)) { if (!primera) archivo << ","; archivo << "caja"; primera = false; }
        if (a->tieneAmenidad(4)) { if (!primera) archivo << ","; archivo << "parqueadero"; primera = false; }
        if (a->tieneAmenidad(5)) { if (!primera) archivo << ","; archivo << "patio"; primera = false; }
        if (a->tieneAmenidad(6)) { if (!primera) archivo << ","; archivo << "cocina"; }

        archivo << "\n";
        totalIteraciones++;
    }

    archivo.close();
}
// Guarda todas las reservas vigentes (formato idéntico a reservas históricas)
void UdeAStay::guardarReservasVigentes(const char* ruta) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) return;

    archivosAbiertos++;
    for (int i = 0; i < cantidadReservasVigentes; i++) {
        Reserva* r = listaReservasVigentes[i];

        archivo << r->getCodigo() << ";"
                << r->getFechaEntrada().getDia() << "-"
                << r->getFechaEntrada().getMes() << "-"
                << r->getFechaEntrada().getAnio() << ";"
                << r->getDuracion() << ";"
                << r->getAlojamiento()->getCodigo() << ";"
                << r->getHuesped()->getDocumentoIdentidad() << ";"
                << r->getMetodoPago() << ";"
                << r->getFechaPago().getDia() << "-"
                << r->getFechaPago().getMes() << "-"
                << r->getFechaPago().getAnio() << ";"
                << r->getMonto() << ";"
                << r->getAnotaciones() << "\n";

        totalIteraciones++;
    }

    archivo.close();
}
// Guarda todas las reservas históricas en el mismo formato que las vigentes
void UdeAStay::guardarReservasHistoricas(const char* ruta) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) return;

    archivosAbiertos++;
    for (int i = 0; i < cantidadReservasHistoricas; i++) {
        Reserva* r = listaReservasHistoricas[i];

        archivo << r->getCodigo() << ";"
                << r->getFechaEntrada().getDia() << "-"
                << r->getFechaEntrada().getMes() << "-"
                << r->getFechaEntrada().getAnio() << ";"
                << r->getDuracion() << ";"
                << r->getAlojamiento()->getCodigo() << ";"
                << r->getHuesped()->getDocumentoIdentidad() << ";"
                << r->getMetodoPago() << ";"
                << r->getFechaPago().getDia() << "-"
                << r->getFechaPago().getMes() << "-"
                << r->getFechaPago().getAnio() << ";"
                << r->getMonto() << ";"
                << r->getAnotaciones() << "\n";

        totalIteraciones++;
    }

    archivo.close();
}
// Guarda la fecha de corte en formato dd-mm-aaaa (una sola línea)
void UdeAStay::guardarFechaCorte(const char* ruta, const Fecha& fecha) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) return;

    archivosAbiertos++;
    archivo << fecha.getDia() << "-"
            << fecha.getMes() << "-"
            << fecha.getAnio() << "\n";

    archivo.close();
}

// Convierte una cadena de texto a entero sin usar atoi
int UdeAStay::convertirEntero(const char* texto) {
    int resultado = 0;
    int i = 0;
    bool negativo = false;

    if (texto[0] == '-') {
        negativo = true;
        i++;
    }

    while (texto[i] != '\0') {
        resultado = resultado * 10 + (texto[i] - '0');
        totalIteraciones++;
        i++;
    }

    return negativo ? -resultado : resultado;
}

// Convierte una cadena de texto a double sin usar atof
double UdeAStay::convertirDouble(const char* texto) {
    double resultado = 0.0;
    double parteDecimal = 0.0;
    bool negativo = false;
    bool enDecimal = false;
    double divisor = 10.0;

    int i = 0;
    if (texto[0] == '-') {
        negativo = true;
        i++;
    }

    while (texto[i] != '\0') {
        if (texto[i] == '.') {
            enDecimal = true;
            i++;
            continue;
        }

        if (!enDecimal) {
            resultado = resultado * 10 + (texto[i] - '0');
        } else {
            parteDecimal += (texto[i] - '0') / divisor;
            divisor *= 10;
        }

        totalIteraciones++;
        i++;
    }

    resultado += parteDecimal;
    return negativo ? -resultado : resultado;
}

// Crea una reserva desde una línea de texto (formato del archivo .txt)
void UdeAStay::crearReservaDesdeTexto(const char* linea) {
    char* cod = extraerCampo(linea, 0);
    char* fechaTexto = extraerCampo(linea, 1);
    char* duracionTexto = extraerCampo(linea, 2);
    char* codAloj = extraerCampo(linea, 3);
    char* docHuesped = extraerCampo(linea, 4);
    char* metodo = extraerCampo(linea, 5);
    char* fechaPagoTexto = extraerCampo(linea, 6);
    char* montoTexto = extraerCampo(linea, 7);
    char* anotaciones = extraerCampo(linea, 8);

    // Procesar fecha entrada
    int d, m, a;
    sscanf(fechaTexto, "%d-%d-%d", &d, &m, &a);
    Fecha fechaEntrada(d, m, a);

    // Procesar fecha pago
    sscanf(fechaPagoTexto, "%d-%d-%d", &d, &m, &a);
    Fecha fechaPago(d, m, a);

    int duracion = convertirEntero(duracionTexto);
    double monto = convertirDouble(montoTexto);

    Alojamiento* aloj = buscarAlojamientoPorCodigo(codAloj);
    Huesped* huesp = buscarHuespedPorDocumento(docHuesped);

    if (!aloj || !huesp) {
        // No se puede crear reserva si el alojamiento o huésped no existen
        delete[] cod; delete[] fechaTexto; delete[] duracionTexto;
        delete[] codAloj; delete[] docHuesped; delete[] metodo;
        delete[] fechaPagoTexto; delete[] montoTexto; delete[] anotaciones;
        return;
    }

    Reserva* nueva = new Reserva(cod, fechaEntrada, duracion, aloj, huesp, metodo, fechaPago, monto, anotaciones);

    // Decidimos si es histórica o vigente según la fecha de salida
    Fecha salida = nueva->calcularFechaSalida();
    if (salida < fechaCorte) {
        if (cantidadReservasHistoricas == capacidadReservasHistoricas)
            redimensionarReservasHistoricas();
        listaReservasHistoricas[cantidadReservasHistoricas++] = nueva;
    } else {
        if (cantidadReservasVigentes == capacidadReservasVigentes)
            redimensionarReservasVigentes();
        listaReservasVigentes[cantidadReservasVigentes++] = nueva;
    }

    aloj->agregarReservacion(fechaEntrada, duracion);
    huesp->agregarReserva(nueva);

    totalMemoria += sizeof(Reserva);

    // Ajustar siguienteId si es necesario
    int idNum = convertirEntero(cod + 4); // Salta "RSV-"
    if (idNum >= Reserva::getSiguienteId()) {
        Reserva::setSiguienteId(idNum + 1);
    }

    delete[] cod; delete[] fechaTexto; delete[] duracionTexto;
    delete[] codAloj; delete[] docHuesped; delete[] metodo;
    delete[] fechaPagoTexto; delete[] montoTexto; delete[] anotaciones;
}
// SECCIÓN 7: CONSTRUCTOR Y DESTRUCTOR
// Constructor principal: inicializa las listas y contadores
UdeAStay::UdeAStay() {
    // Capacidades iniciales para cada lista dinámica
    capacidadAnfitriones = 10;
    capacidadHuespedes = 10;
    capacidadAlojamientos = 10;
    capacidadReservasVigentes = 20;
    capacidadReservasHistoricas = 20;

    cantidadAnfitriones = 0;
    cantidadHuespedes = 0;
    cantidadAlojamientos = 0;
    cantidadReservasVigentes = 0;
    cantidadReservasHistoricas = 0;

    // Inicializamos las listas con punteros dinámicos
    listaAnfitriones = new Anfitrion*[capacidadAnfitriones];
    listaHuespedes = new Huesped*[capacidadHuespedes];
    listaAlojamientos = new Alojamiento*[capacidadAlojamientos];
    listaReservasVigentes = new Reserva*[capacidadReservasVigentes];
    listaReservasHistoricas = new Reserva*[capacidadReservasHistoricas];

    // Métricas del sistema
    totalIteraciones = 0;
    totalMemoria = 0;
    archivosAbiertos = 0;
    lineasLeidas = 0;

    // Inicializamos la fecha de corte por defecto
    fechaCorte = Fecha(1, 1, 2000);

    // Registro de memoria para las listas principales (no incluye objetos internos)
    totalMemoria += (capacidadAnfitriones * sizeof(Anfitrion*));
    totalMemoria += (capacidadHuespedes * sizeof(Huesped*));
    totalMemoria += (capacidadAlojamientos * sizeof(Alojamiento*));
    totalMemoria += (capacidadReservasVigentes * sizeof(Reserva*));
    totalMemoria += (capacidadReservasHistoricas * sizeof(Reserva*));
}

// Destructor: libera toda la memoria dinámica usada por el sistema
UdeAStay::~UdeAStay() {
    // Eliminamos anfitriones
    for (int i = 0; i < cantidadAnfitriones; i++) {
        delete listaAnfitriones[i];
        totalIteraciones++;
    }
    delete[] listaAnfitriones;

    // Eliminamos huéspedes
    for (int i = 0; i < cantidadHuespedes; i++) {
        delete listaHuespedes[i];
        totalIteraciones++;
    }
    delete[] listaHuespedes;

    // Eliminamos alojamientos
    for (int i = 0; i < cantidadAlojamientos; i++) {
        delete listaAlojamientos[i];
        totalIteraciones++;
    }
    delete[] listaAlojamientos;

    // Eliminamos reservas vigentes
    for (int i = 0; i < cantidadReservasVigentes; i++) {
        delete listaReservasVigentes[i];
        totalIteraciones++;
    }
    delete[] listaReservasVigentes;

    // Eliminamos reservas históricas
    for (int i = 0; i < cantidadReservasHistoricas; i++) {
        delete listaReservasHistoricas[i];
        totalIteraciones++;
    }
    delete[] listaReservasHistoricas;
}
// SECCIÓN 8: FUNCIONALIDADES PRINCIPALES

// Carga todos los datos del sistema desde los archivos fuente
void UdeAStay::cargarDatosDesdeArchivos() {
    cargarFechaCorte("../codigo/datos/fecha_corte.txt");
    cargarAnfitriones("../codigo/datos/anfitriones.txt");
    cargarHuespedes("../codigo/datos/huespedes.txt");
    cargarAlojamientos("../codigo/datos/alojamientos.txt");
    cargarReservasVigentes("../codigo/datos/reservas_vigentes.txt");
    cargarReservasHistoricas("../codigo/datos/reservas_historicas.txt");
}
// Guarda todos los datos actuales del sistema en sus respectivos archivos
void UdeAStay::guardarDatosEnArchivos() {
    guardarAnfitriones("../codigo/datos/anfitriones.txt");
    guardarHuespedes("../codigo/datos/huespedes.txt");
    guardarAlojamientos("../codigo/datos/alojamientos.txt");
    guardarReservasVigentes("../codigo/datos/reservas_vigentes.txt");
    guardarReservasHistoricas("../codigo/datos/reservas_historicas.txt");
    guardarFechaCorte("../codigo/datos/fecha_corte.txt", fechaCorte);
}
// Busca al usuario (anfitrión o huésped) y muestra un saludo si existe
bool UdeAStay::iniciarSesion(const char* documento, int tipoUsuario) {
    // Limpiar sesión previa
    anfitrionActivo = nullptr;
    huespedActivo   = nullptr;

    if (tipoUsuario == TIPO_ANFITRION) {
        anfitrionActivo = buscarAnfitrionPorDocumento(documento);
        if (anfitrionActivo) {
            cout << "Bienvenido, anfitrion " << anfitrionActivo->getNombreCompleto() << "!\n";
            return true;
        }
    }
    else if (tipoUsuario == TIPO_HUESPED) {
        huespedActivo = buscarHuespedPorDocumento(documento);
        if (huespedActivo) {
            cout << "Bienvenido, huesped " << huespedActivo->getNombreCompleto() << "!\n";
            return true;
        }
    }

    cout << "Credenciales invalidas.\n";
    return false;
}

void UdeAStay::cerrarSesion() {
    if (anfitrionActivo) {
        cout << "Sesión de anfitrión finalizada.\n";
    }
    if (huespedActivo) {
        cout << "Sesión de huésped finalizada.\n";
    }
    anfitrionActivo = nullptr;
    huespedActivo   = nullptr;
}
// Intenta crear una nueva reserva si el huésped y el alojamiento existen, y hay disponibilidad
void UdeAStay::crearReserva(const char* documentoHuesped,
                            const char* codigoAlojamiento,
                            const Fecha& fechaEntrada,
                            int duracion,
                            int metodoPago,
                            const Fecha& fechaPago,
                            double monto,
                            const char* anotaciones) {

    Huesped* h = buscarHuespedPorDocumento(documentoHuesped);
    Alojamiento* a = buscarAlojamientoPorCodigo(codigoAlojamiento);

    if (!h || !a) {
        cout << "Error: huesped o alojamiento no encontrado." << endl;
        return;
    }

    if (!validarDisponibilidad(a, fechaEntrada, duracion)) {
        cout << "Error: el alojamiento no esta disponible." << endl;
        return;
    }

    Reserva* nueva = new Reserva(fechaEntrada, duracion, a, h,
                                 metodoPago == METODO_PSE ? "PSE" : "TCredito",
                                 fechaPago, monto, anotaciones);

    if (cantidadReservasVigentes == capacidadReservasVigentes)
        redimensionarReservasVigentes();

    listaReservasVigentes[cantidadReservasVigentes++] = nueva;
    a->agregarReservacion(fechaEntrada, duracion);
    h->agregarReserva(nueva);

    totalMemoria += sizeof(Reserva);

    cout << "Reserva creada exitosamente. Codigo: " << nueva->getCodigo() << endl;
}
// Busca y elimina una reserva tanto del huésped como del alojamiento
void UdeAStay::anularReserva(const char* codigoReserva) {
    for (int i = 0; i < cantidadReservasVigentes; i++) {
        if (sonIguales(listaReservasVigentes[i]->getCodigo(), codigoReserva)) {
            Huesped* h = listaReservasVigentes[i]->getHuesped();
            Alojamiento* a = listaReservasVigentes[i]->getAlojamiento();

            if (a) {
                a->eliminarReservacion(listaReservasVigentes[i]->getFechaEntrada(),
                                       listaReservasVigentes[i]->getDuracion());
            }
            Fecha fecha = listaReservasVigentes[i]->getFechaEntrada();
            int duracion = listaReservasVigentes[i]->getDuracion();
            if (h) {
                h->anularReservacion(fecha, duracion);    // Luego del huésped
            }

            delete listaReservasVigentes[i];
            for (int j = i; j < cantidadReservasVigentes - 1; j++) {
                listaReservasVigentes[j] = listaReservasVigentes[j + 1];
            }
            cantidadReservasVigentes--;

            cout << "Reserva anulada exitosamente." << endl;
            return;
        }
    }

    cout << "No se encontró ninguna reserva con ese codigo." << endl;
}
// Muestra las reservas en rango para todos los alojamientos de un anfitrión
void UdeAStay::consultarReservasAnfitrion(const char* documentoAnfitrion,
                                          const Fecha& desde,
                                          const Fecha& hasta) {
    Anfitrion* a = buscarAnfitrionPorDocumento(documentoAnfitrion);
    if (!a) {
        cout << "Anfitrion no encontrado." << endl;
        return;
    }

    a->verReservaciones(desde, hasta);
}
// Mueve todas las reservas anteriores a la nueva fecha de corte al histórico
void UdeAStay::actualizarHistorico(const Fecha& nuevaFechaCorte) {
    for (int i = 0; i < cantidadReservasVigentes; ) {
        Fecha entrada = listaReservasVigentes[i]->getFechaEntrada();
        Fecha salida = listaReservasVigentes[i]->calcularFechaSalida();

        if (salida < nuevaFechaCorte) {
            Reserva* movida = listaReservasVigentes[i];

            if (cantidadReservasHistoricas == capacidadReservasHistoricas)
                redimensionarReservasHistoricas();

            listaReservasHistoricas[cantidadReservasHistoricas++] = movida;

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
}
// Muestra el uso de recursos del sistema actual
void UdeAStay::medirConsumoDeRecursos() {
    cout << "Metricas de rendimiento:" << endl;
    cout << "Total de iteraciones:  " << totalIteraciones << endl;
    cout << "Memoria dinamica (bytes): " << totalMemoria << endl;
    cout << "Archivos abiertos:     " << archivosAbiertos << endl;
    cout << "Líneas leidas:         " << lineasLeidas << endl;
    cout << "===================================" << endl;
}



