#include "sniper.h"

#define SNIPER "Sniper"
#define ALCANCE 64
#define MUNICIONES 3

Sniper::Sniper(): Arma(ID_SNIPER, SNIPER, ALCANCE, MUNICIONES, false) {}

void Sniper::disparar(const orientacion_e& direccion) { return; }