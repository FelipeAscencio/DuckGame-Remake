#include "caja.h"

#define CERO 0

Caja::Caja(const posicion_t& pos, const int& id_caja):
        posicion(pos), estado(INTACTA), destruida(false), id(id_caja), contenido(CERO) {}

void Caja::recibir_disparo() {
    mtx = std::make_unique<std::mutex>();
    std::lock_guard<std::mutex> lck(*mtx);
    if (estado == INTACTA) {
        estado = ROTA;
    } else if (estado == ROTA) {
        estado = MUY_ROTA;
    } else {
        destruida = true;
    }
}

int Caja::destruir() {
    mtx = std::make_unique<std::mutex>();
    std::lock_guard<std::mutex> lck(*mtx);
    contenido = rand() % 4;
    return contenido;
}
