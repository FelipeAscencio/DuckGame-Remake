#include "magnum.h"

#define MAGNUM "Magnum"
#define ALCANCE 20
#define MUNICIONES 6

Magnum::Magnum(): Arma(ID_MAGNUM, MAGNUM, ALCANCE, MUNICIONES, true) {}

void Magnum::disparar(const orientacion_e& direccion) { return; }