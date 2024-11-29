#include "spawn_place.h"

#define ITERACIONES_MINIMAS_RESPAWN 180
#define CERO 0
#define UNO 1
#define CANTIDAD_ITEM_LOOTEABLES 10
#define VARIANTES_DE_LOOT 3

Spawn::Spawn(posicion_t pos):
        posicion(pos),
        iteraciones_desde_spawn(CERO),
        nro_random_spawn(rand() % CANTIDAD_ITEM_LOOTEABLES),
        libre(true),
        contenido(CERO) {}

void Spawn::liberar() {
    mtx = std::make_unique<std::mutex>();
    std::lock_guard<std::mutex> lck(*mtx);
    this->libre = true;
    iteraciones_desde_spawn = CERO;
    contenido = CERO;
}

bool Spawn::spawnear() {
    mtx = std::make_unique<std::mutex>();
    std::lock_guard<std::mutex> lck(*mtx);
    this->iteraciones_desde_spawn++;
    if (!libre)
        return false;

    if (iteraciones_desde_spawn < ITERACIONES_MINIMAS_RESPAWN)
        return false;

    if (iteraciones_desde_spawn % ConfigJuego::FPS == CERO) {
        if (rand() % CANTIDAD_ITEM_LOOTEABLES != nro_random_spawn)
            return false;

        libre = false;
        contenido = (rand() % VARIANTES_DE_LOOT) + UNO;
        return true;
    }

    return false;
}
