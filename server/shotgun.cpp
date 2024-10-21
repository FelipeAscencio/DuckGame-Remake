#include "shotgun.h"

#define SHOTGUN "Shotgun"
#define ALCANCE_MINIMO 7
#define ALCANCE_MAXIMO 9
#define MUNICIONES 2

Shotgun::Shotgun():
        Arma(SHOTGUN, ALCANCE_MINIMO, MUNICIONES, true),
        debe_recargar(false),
        alcance_maximo(ALCANCE_MAXIMO) {}

void Shotgun::disparar() { return; }