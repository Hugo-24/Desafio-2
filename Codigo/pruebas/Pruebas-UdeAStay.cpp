#include <iostream>
#include "Fecha.h"

int main() {
    Fecha f1(17, 5, 2025);
    Fecha f2(18, 5, 2025);

    if (f1 < f2) {
        std::cout << "f1 es anterior a f2" << std::endl;
    }

    char* texto = f1.toString();
    std::cout << "f1: " << texto << std::endl;
    delete[] texto;

    Fecha f3 = f1;
    if (f1 == f3) {
        std::cout << "f1 y f3 son iguales" << std::endl;
    }

    return 0;
}
