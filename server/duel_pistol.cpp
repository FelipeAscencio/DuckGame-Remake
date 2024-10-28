#include "duel_pistol.h"

#define DUEL_PISTOL "Duel Pistol"
#define ALCANCE 5
#define MUNICIONES 1

DuelPistol::DuelPistol(): Arma(ID_DUEL_PISTOL, DUEL_PISTOL, ALCANCE, MUNICIONES, true) {}

void DuelPistol::disparar(const orientacion_e& direccion) { return; }