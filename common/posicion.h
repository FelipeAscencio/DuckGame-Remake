// Copyright 2024 Axel Zielonka y Felipe Ascensio
#ifndef COMMON_POSICION_H_
#define COMMON_POSICION_H_

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

typedef struct Posicion {
    float coordenada_x;
    float coordenada_y;

    // Constructor por defecto
    Posicion(): coordenada_x(0), coordenada_y(0) {}

    // Constructor por parámetros
    Posicion(float x, float y): coordenada_x(x), coordenada_y(y) {}

    // Constructor de copia
    Posicion(const Posicion& pos): coordenada_x(pos.coordenada_x), coordenada_y(pos.coordenada_y) {}

    // Operador de asignación
    Posicion& operator=(const Posicion& pos) {
        if (this != &pos) {
            coordenada_x = pos.coordenada_x;
            coordenada_y = pos.coordenada_y;
        }
        return *this;
    }

    void set_posicion(float x, float y) {
        coordenada_x = x;
        coordenada_y = y;
    }

    std::string to_string() {
        std::ostringstream oss;
        oss << "(" << coordenada_x << ";" << coordenada_y << ")\n";
        return oss.str();
    }

    bool misma_posicion(const posicion_t& otra){
        return this->coordenada_x == otra.coordenada_x && abs(this->coordenada_y - otra.coordenada_y) <= TILE_A_METRO/2;
    }
} posicion_t;

#endif  // COMMON_POSICION_H_
