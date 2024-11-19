// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef SERVER_MAPA_H_
#define SERVER_MAPA_H_

#include <iostream>
#include <vector>

#include "../common/orientacion.h"
#include "../common/posicion.h"

#define TILE_A_METRO 10

// 'struct' auxiliar para encapsular un error.
struct ErrorMapa: public std::runtime_error {
    ErrorMapa(): std::runtime_error("Se produjo un error al intentar crear el mapa") {}
};

// La clase 'Mapa' implementa la logica del funcionamiento
// del mapa y su rol en el juego.
class Mapa {
    friend class Pato;
    friend class Municion;
    friend class Gameloop;

private:
    int largo;
    int alto;
    int** mapa;
    int id_mapa;

public:
    // Constructor de la clase.
    explicit Mapa(int mapa);

    // Convierte una posicion en coordenadas del mapa a unidades de "tiles".
    std::vector<int> posicion_en_mapa(const posicion_t& posicion);

    // Verifica si una posicion esta en el borde de un bloque segun la orientacion dada.
    bool borde_bloque(const posicion_t& pos, const orientacion_e& orientacion);

    // Verifica si una posicion esta en el limite inferior (piso) de un bloque.
    bool piso_bloque(const posicion_t& pos);

    bool techo_bloque(const posicion_t& pos);

    posicion_t posicion_inicial(const int& id_jugador);

    // Destructor de la clase.
    ~Mapa();
};

#endif  // SERVER_MAPA_H_
