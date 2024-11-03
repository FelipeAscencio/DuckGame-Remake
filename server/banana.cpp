#include "banana.h"

#include <iostream>

#define BANANA "Banana"
#define ALCANCE 5
#define MUNICIONES 1

Banana::Banana(posicion_t posicion_inicial): Arma(ID_BANANA, BANANA, ALCANCE, MUNICIONES, false, posicion_inicial), activa(false) {}

bool Banana::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA || direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
        return true;
    } else {
        std::cout << "Direccion invalida" << std::endl;
        return false;
    }
}

void Banana::chequeo_balas() {
    std::cout << "Nada por ahora" << std::endl;
    return;
}
