#include "duel_pistol.h"

#define DUEL_PISTOL "Duel Pistol"
#define ALCANCE 5
#define MUNICIONES 1

DuelPistol::DuelPistol(): Arma(DUEL_PISTOL, ALCANCE, MUNICIONES, true) {}

void DuelPistol::disparar() { return; }