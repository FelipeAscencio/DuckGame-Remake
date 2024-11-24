#ifndef CAJA_H
#define CAJA_H

#include <iostream>
#include <mutex>
#include <memory>
#include "../common/posicion.h"

enum damage_e{
    INTACTA, ROTA, MUY_ROTA
};

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
        Caja(const posicion_t& posicion, const int& id);

        void recibir_disparo();

        int destruir();

        Caja(Caja&& otro) = default;
        Caja& operator=(Caja&& other) noexcept = default;
};

#endif