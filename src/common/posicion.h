// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef COMMON_POSICION_H_
#define COMMON_POSICION_H_

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#define CERO 0
#define CERO_Y_MEDIO 0.5
#define UNO 1
#define UNO_Y_MEDIO 1.5
#define DOS 2
#define TILE_A_METRO 10

// 'Struct' que define la posicion en relacion al eje 'X' e 'Y' de una entidad.
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
    bool misma_posicion(Posicion otra) {
        float dx = abs(this->coordenada_x - otra.coordenada_x);
        float dy = abs(this->coordenada_y - otra.coordenada_y);
        bool resultado = (dx < CERO_Y_MEDIO && dy <= (TILE_A_METRO - UNO));
        return resultado;
    }

    // Se fija si el 'Pato' puede agarrar el loot, si es asi devuelve 'true', caso contrario devuelve 'false'.
    bool igual_para_pickup(const Posicion& otra){
        float dx = abs(this->coordenada_x - otra.coordenada_x);
        float dy = abs(this->coordenada_y - otra.coordenada_y);
        bool resultado = dx <= UNO_Y_MEDIO && dy <= TILE_A_METRO /DOS;
        return resultado;
    }
    
} posicion_t;

#endif  // COMMON_POSICION_H_
