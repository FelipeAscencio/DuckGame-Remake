#include "cowboy_pistol.h"

#define COWBOY_PISTOL "Cowboy Pistol"
#define ALCANCE 20
#define MUNICIONES 6

CowboyPistol::CowboyPistol(): Arma(COWBOY_PISTOL, ALCANCE, MUNICIONES, false) {}

void CowboyPistol::disparar() { return; }