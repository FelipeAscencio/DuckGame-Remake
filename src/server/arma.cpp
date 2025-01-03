#include "arma.h"

#define CERO 0
#define UNO 1
#define DIFERENCIA_SPAWN_BALA 3

Arma::Arma(const int& id, const std::string& nombre_arma, const int& alcance, const int& municiones,
           bool tiene_retroceso, posicion_t posicion_inicial):
        id_arma(id),
        nombre(nombre_arma),
        alcance(alcance),
        municiones_iniciales(municiones),
        municiones(municiones),
        retroceso(tiene_retroceso),
        posicion_spawn(posicion_inicial),
        agarrada(false),
        soltada(false) {}

void Arma::recargar() { this->municiones = municiones_iniciales; }

bool Arma::tiene_retroceso() { return this->retroceso; }

int Arma::municiones_restantes() { return this->municiones; }

void Arma::eliminar_bala(const int& indice) {
    balas.erase(balas.begin() + indice);
    for (int i = indice; i < (int)balas.size(); i++) {
        balas[i].nro_bala -= UNO;
    }
}

void Arma::chequeo_balas(Mapa& mapa) {
    if (this->municiones == CERO) {
        this->agarrada = false;
        this->soltada = true;
    }

    bool no_borre_ninguno = false;
    while (!no_borre_ninguno) {
        no_borre_ninguno = true;
        size_t i = CERO;
        while (i < balas.size()) {
            if (balas[i].fuera_de_rango(mapa)) {
                eliminar_bala(i);
                no_borre_ninguno = false;
                break;
            } else {
                if (balas[i].avanzar(mapa)) {
                    i++;
                } else {
                    eliminar_bala(i);
                    no_borre_ninguno = false;
                    break;
                }
            }
        }
    }
}

posicion_t Arma::ajustar_posicion_disparo(const orientacion_e& direccion) {
    float dx = CERO;
    float dy = CERO;
    if (direccion == DERECHA) {
        dx = DIFERENCIA_SPAWN_BALA;
    } else if (direccion == IZQUIERDA) {
        dx = -DIFERENCIA_SPAWN_BALA;
    } else {
        dy = -DIFERENCIA_SPAWN_BALA;
    }

    return (posicion_t(this->posicion_spawn.coordenada_x + dx,
                       this->posicion_spawn.coordenada_y + dy));
}

void Arma::control_atributos(Mapa& mapa) { chequeo_balas(mapa); }

Arma::~Arma() {
    balas.clear();
    municiones = CERO;
    soltada = true;
}
