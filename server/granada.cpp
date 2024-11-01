#include "granada.h"

#include <iostream>

#define GRANADA "Granada"
#define ALCANCE 5
#define MUNICION 1
#define TIEMPO_HASTA_EXPLOTAR 4

Granada::Granada():
        Arma(ID_GRANADA, GRANADA, ALCANCE, MUNICION, false),
        tiempo_hasta_explotar(TIEMPO_HASTA_EXPLOTAR),
        seguro_puesto(true),
        activa(false) {}

bool Granada::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA || direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
        return true;
    } else {
        std::cout << "Direccion invalida" << std::endl;
        return false;
    }
}

void Granada::chequeo_balas() {
    std::cout << "Nada por ahora" << std::endl;
    return;
}
