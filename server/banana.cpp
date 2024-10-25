#include "banana.h"

#define BANANA "Banana"
#define ALCANCE 5
#define MUNICIONES 1

Banana::Banana(): Arma(ID_BANANA, BANANA, ALCANCE, MUNICIONES, false), activa(false) {}

void Banana::disparar(const orientacion_e& direccion) { return; }