// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef COMMON_POSICION_H_
#define COMMON_POSICION_H_

#include <iostream>
#include <sstream>
#include <string>

// 'struct' que define la posicion en relacion al eje 'X' e 'Y' de una entidad.
typedef struct Posicion {
    int coordenada_x;
    int coordenada_y;

    // Constructor por defecto.
    Posicion(): coordenada_x(0), coordenada_y(0) {}

    // Constructor por parametros.
    Posicion(int x, int y): coordenada_x(x), coordenada_y(y) {}

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

    // Setea el nuevo valor de 'X' e 'Y'.
    void set_posicion(int x, int y) {
        coordenada_x = x;
        coordenada_y = y;
    }

    // Convierte las coordenadas en 'string'.
    std::string to_string() {
        std::ostringstream oss;
        oss << "(" << coordenada_x << ";" << coordenada_y << ")\n";
        return oss.str();
    }
    
} posicion_t;

#endif  // COMMON_POSICION_H_
