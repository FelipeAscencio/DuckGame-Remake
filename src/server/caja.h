#ifndef CAJA_H
#define CAJA_H

#include <iostream>
#include "../common/posicion.h"

enum damage_e{
    INTACTA, ROTA, MUY_ROTA
};

class Caja{
    friend class Gameloop;
    friend struct InformacionCaja;
    private:
        posicion_t posicion;
        damage_e estado;
        bool destruida;
        int id;
    public:
        Caja(const posicion_t& posicion, const int& id);

        void recibir_disparo();

        int destruir();
};

#endif