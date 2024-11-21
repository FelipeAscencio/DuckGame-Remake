#include "spawn_place.h"

#define ITERACIONES_MINIMAS_RESPAWN 150 

Spawn::Spawn(posicion_t pos): posicion(pos), iteraciones_desde_spawn(0), nro_random_spawn(rand() % 10), libre(true), contenido(0){}

void Spawn::liberar() { 
    this->libre = true; 
    iteraciones_desde_spawn = 0;
    contenido = 0;
}

int Spawn::spawnear(){
    iteraciones_desde_spawn += 1;
    if(!libre) return 0;
    if (iteraciones_desde_spawn < ITERACIONES_MINIMAS_RESPAWN) return 0;
    if (rand() % 10 != nro_random_spawn) return 0;
    libre = false;
    contenido = (rand()%3) + 1;
    return contenido;
}

