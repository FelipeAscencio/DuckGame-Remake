#ifndef SPAWN_PLACE_H
#define SPAWN_PLACE_H

#include <iostream>
#include "../common/posicion.h"
#include <mutex>
#include <utility>
#include <memory>

class Spawn{
    friend class Mapa;
    friend class Pato;
    friend class Gameloop;
    private:
        const posicion_t posicion;
        int iteraciones_desde_spawn;
        int nro_random_spawn;
        bool libre;
        int contenido;
        std::unique_ptr<std::mutex> mtx;
    public:
        Spawn(posicion_t posicion);

        bool spawnear();

        void liberar();

};


#endif