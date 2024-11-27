// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef CAJA_H
#define CAJA_H

#include <iostream>
#include <mutex>
#include <memory>
#include "../common/posicion.h"

// 'Enum' que encapsula los posibles estados de la 'Caja'.
enum damage_e{
    INTACTA, ROTA, MUY_ROTA
};

// La clase 'Caja' implementa toda la logica relacionada a las cajas
// del juego, controla sus estados y sus posibles interacciones en el transcurso del juego.
class Caja{
friend class Gameloop;
friend struct InformacionCaja;
friend class Pato;

private:
    posicion_t posicion;
    damage_e estado;
    bool destruida;
    int id;
    std::unique_ptr<std::mutex> mtx;
    int contenido;

public:
    // Constructor de la clase
    Caja(const posicion_t& posicion, const int& id);

    // Recibe el impacto de una bala y cambia el estado de la caja segun corresponda.
    void recibir_disparo();

    // Destruye la caja, y hace el 'rand' para ver si da 'loot' o no.
    int destruir();

    // Constructor por movimiento.
    Caja(Caja&& otro) = default;

    // Operador de asignacion por movimiento.
    Caja& operator=(Caja&& other) noexcept = default;
};

#endif  // CAJA_H
