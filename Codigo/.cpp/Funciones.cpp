#include "Funciones.h"

long totalIteracionesGlobales = 0;
long totalMemoriaGlobal = 0;

// Implementación de copiarTexto
char* copiarTexto(const char* fuente) {
    if (!fuente) return nullptr;

    int len = 0;
    while (fuente[len] != '\0') {
        len++;
        totalIteracionesGlobales++;
    }

    char* copia = new char[len + 1];
    totalMemoriaGlobal += (len + 1) * sizeof(char);

    for (int i = 0; i <= len; i++) {
        copia[i] = fuente[i];
        totalIteracionesGlobales++;
    }

    return copia;
}

// Implementación de sonIguales
bool sonIguales(const char* a, const char* b) {
    if (!a || !b) return false;
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        totalIteracionesGlobales++;
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

// Implementación de iniciaCon
bool iniciaCon(const char* texto, const char* prefijo) {
    if (!texto || !prefijo) return false;
    int i = 0;
    while (prefijo[i] != '\0') {
        totalIteracionesGlobales++;
        if (texto[i] == '\0' || texto[i] != prefijo[i]) return false;
        i++;
    }
    return true;
}
