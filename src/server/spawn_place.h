#ifndef SPAWN_PLACE_H
#define SPAWN_PLACE_H

#include <iostream>
#include "../common/posicion.h"

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
    
    public:
        Spawn(posicion_t posicion);

        int spawnear();

        void liberar();

};


#endif