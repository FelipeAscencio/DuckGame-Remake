#include "laser_rifle.h"

#define LASER_RIFLE "Laser Rifle"
#define ALCANCE 30
#define MUNICIONES 10

LaserRifle::LaserRifle(): Arma(LASER_RIFLE, ALCANCE, MUNICIONES, false) {}

void LaserRifle::disparar() { return; }