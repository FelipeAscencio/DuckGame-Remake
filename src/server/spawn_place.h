// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef SPAWN_PLACE_H
#define SPAWN_PLACE_H

#include <iostream>
#include "../common/posicion.h"
#include <mutex>
#include <utility>
#include <memory>

// La clase 'Spawn' implementa la logica de los Spawn Places.
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
    // Constructor de la clase.
    Spawn(posicion_t posicion);

    // Spawnea un nuevo 'loot' en la zona de 'Spawn'.
    bool spawnear();

    // Libera el 'Spawn' una vez que se lotea, para empezar la regeneracion del nuevo 'loot'.
    void liberar();

    // Deshabilito las copias.
    Spawn(const Spawn&) = delete;
    Spawn& operator=(const Spawn&) = delete;

    // Permito el movimiento del objeto.
    Spawn(Spawn&&) = default;
    Spawn& operator=(Spawn&&) = default;
};

#endif  // SPAWN_PLACES_H_
