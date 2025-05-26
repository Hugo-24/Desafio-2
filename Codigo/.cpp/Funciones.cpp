#include "Funciones.h"

// Implementación de copiarTexto
char* copiarTexto(const char* fuente) {
    if (!fuente) return nullptr;

    int len = 0;
    while (fuente[len] != '\0') len++;

    char* copia = new char[len + 1];
    for (int i = 0; i <= len; i++) {
        copia[i] = fuente[i];
    }

    return copia;
}

// Implementación de sonIguales
bool sonIguales(const char* a, const char* b) {
    if (!a || !b) return false;
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
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
        if (texto[i] == '\0' || texto[i] != prefijo[i]) return false;
        i++;
    }
    return true;
}
