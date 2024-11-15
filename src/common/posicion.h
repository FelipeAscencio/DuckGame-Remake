// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef COMMON_POSICION_H_
#define COMMON_POSICION_H_

#include <iostream>
#include <sstream>
#include <string>

#include <math.h>

#define CERO 0
#define DOS 2
#define TILE_A_METRO 10

// 'struct' que define la posicion en relacion al eje 'X' e 'Y' de una entidad.
typedef struct Posicion {
    float coordenada_x;
    float coordenada_y;

    // Constructor por defecto.
    Posicion(): coordenada_x(CERO), coordenada_y(CERO) {}

    // Constructor por parámetros
    Posicion(float x, float y): coordenada_x(x), coordenada_y(y) {}

    // Constructor por copia.
    Posicion(const Posicion& pos): coordenada_x(pos.coordenada_x), coordenada_y(pos.coordenada_y) {}

    // Operador de asignacion.
    Posicion& operator=(const Posicion& pos) {
        if (this != &pos) {
            coordenada_x = pos.coordenada_x;
            coordenada_y = pos.coordenada_y;
        }
        return *this;
    }

    // Cambia las coordenadas actuales por las recibidas como parametros.
    void set_posicion(float x, float y) {
        coordenada_x = x;
        coordenada_y = y;
    }

    // Convierte las coordenadas en 'string'.
    std::string to_string() {
        std::ostringstream oss;
        oss << "(" << coordenada_x << ";" << coordenada_y << ")\n";
        return oss.str();
    }

    // Compara la posicion propia con otra recibida por parametro, en caso de igualdad devuelve
    // true.
    bool misma_posicion(const Posicion& otra) {
        return this->coordenada_x == otra.coordenada_x &&
               abs(this->coordenada_y - otra.coordenada_y) <= TILE_A_METRO / DOS;
    }
} posicion_t;

#endif  // COMMON_POSICION_H_