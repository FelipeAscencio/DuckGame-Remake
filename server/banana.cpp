#include "banana.h"

#include <iostream>

#define BANANA "Banana"
#define ALCANCE 5
#define MUNICIONES 1

Banana::Banana(): Arma(ID_BANANA, BANANA, ALCANCE, MUNICIONES, false), activa(false) {}

void Banana::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA ||
        direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
    } else {
        std::cout << "Direccion invalida" << std::endl;
    }
}