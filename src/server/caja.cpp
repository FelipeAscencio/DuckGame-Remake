#include "caja.h"


Caja::Caja(const posicion_t& pos, const int& id_caja): posicion(pos), estado(INTACTA), destruida(false), id(id_caja){}

void Caja::recibir_disparo(){
    if (estado == INTACTA)
        estado = ROTA;
    else if (estado == ROTA)
        estado = MUY_ROTA;
    else 
        destruida = true;
}

int Caja::destruir(){
    return rand()%4;
}