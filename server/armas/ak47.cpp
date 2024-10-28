#include "ak47.h"

#define AK_47 "AK-47"
#define ALCANCE 13
#define MUNICIONES 30

AK47::AK47(): Arma(ID_AK47, AK_47, ALCANCE, MUNICIONES, true) {}

void AK47::disparar(const orientacion_e& direccion) { return; }