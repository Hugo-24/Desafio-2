#ifndef FUNCIONES_H
#define FUNCIONES_H

extern long totalIteracionesGlobales;
extern long totalMemoriaGlobal;

// Texto
char* copiarTexto(const char* fuente);
bool sonIguales(const char* a, const char* b);
bool iniciaCon(const char* texto, const char* prefijo);

// Template para redimensionar cualquier arreglo tipo T*
template <typename T>
T** redimensionarArreglo(T** arreglo, int cantidadActual, int& capacidad) {
    int nuevaCapacidad = capacidad * 2;
    T** nuevoArreglo = new T*[nuevaCapacidad];
    for (int i = 0; i < cantidadActual; i++) {
        nuevoArreglo[i] = arreglo[i];
        totalIteracionesGlobales++;
    }
    delete[] arreglo;
    capacidad = nuevaCapacidad;
    totalMemoriaGlobal += nuevaCapacidad * sizeof(T*);
    return nuevoArreglo;
}

#endif
