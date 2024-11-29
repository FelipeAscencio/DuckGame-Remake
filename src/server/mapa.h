// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef SERVER_MAPA_H_
#define SERVER_MAPA_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../common/orientacion.h"
#include "../common/posicion.h"

#include "spawn_place.h"

#define MSJ_ERROR_CREAR_MAPA "Se produjo un error al intentar crear el mapa"

// 'Struct' auxiliar para encapsular un error.
struct ErrorMapa: public std::runtime_error {
    ErrorMapa(): std::runtime_error(MSJ_ERROR_CREAR_MAPA) {}
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

    // Carga el mapa segun el 'id' correspondiente.
    void cargar_mapa(const int& id_mapa);

public:
    // Constructor de la clase.
    Mapa();

    // Convierte una posicion en coordenadas del mapa a unidades de "tiles".
    std::vector<int> posicion_en_mapa(const posicion_t& posicion);

    // Verifica si una posicion esta en el borde de un bloque segun la orientacion dada.
    bool borde_bloque(const posicion_t& pos, const orientacion_e& orientacion);

    // Verifica si una posicion esta en el limite inferior (piso) de un bloque.
    bool piso_bloque(const posicion_t& pos);

    // Verifica si un pato va a chocarse con un techo.
    bool techo_bloque(const posicion_t& pos);

    // Asigna una posicion inicial a un jugador.
    posicion_t posicion_inicial(const int& id_jugador);

    // Inicializa los puntos de spawn segun corresponda.
    void inicializar_puntos_spawn(std::vector<Spawn>& puntos_spawn);

    // Inicializa las posiciones de las cajas segun corresponda.
    posicion_t posicion_caja(const int& id_caja);

    // Resetea el mapa para cambiar de ronda y randomiza el nuevo mapa.
    void resetear();

    // Destructor de la clase.
    ~Mapa();

    // Deshabilito las copias.
    Mapa(const Mapa&) = delete;
    Mapa& operator=(const Mapa&) = delete;

    // Permito el movimiento del objeto.
    Mapa(Mapa&&) = default;
    Mapa& operator=(Mapa&&) = default;
};

#endif  // SERVER_MAPA_H_
