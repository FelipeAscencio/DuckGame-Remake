#include "granada.h"

#define GRANADA "Granada"
#define ALCANCE 5
#define MUNICION 1
#define TIEMPO_HASTA_EXPLOTAR 4

Granada::Granada():
        Arma(ID_GRANADA, GRANADA, ALCANCE, MUNICION, false),
        tiempo_hasta_explotar(TIEMPO_HASTA_EXPLOTAR),
        seguro_puesto(true),
        activa(false) {}

void Granada::disparar(const orientacion_e& direccion) { return; }