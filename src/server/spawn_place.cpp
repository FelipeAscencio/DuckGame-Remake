#include "spawn_place.h"

#define ITERACIONES_MINIMAS_RESPAWN 180 

Spawn::Spawn(posicion_t pos): posicion(pos), iteraciones_desde_spawn(0), nro_random_spawn(rand() % 10), libre(true), contenido(0){}

void Spawn::liberar() { 
    std::lock_guard<std::mutex> lck(mtx);
    this->libre = true; 
    iteraciones_desde_spawn = 0;
    contenido = 0;
}

bool Spawn::spawnear(){
    std::lock_guard<std::mutex> lck(mtx);
    this->iteraciones_desde_spawn++;
    if(!libre) return false; 
    if (iteraciones_desde_spawn < ITERACIONES_MINIMAS_RESPAWN) return false;
    if (iteraciones_desde_spawn % 30 == 0){
        if (rand() % 10 != nro_random_spawn) return false;
        libre = false;
        contenido = (rand()%3) + 1;
        return true;
    }
    return false;
}

