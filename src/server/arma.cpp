#include "arma.h"

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

void Arma::agarrar() { this->agarrada = true; }

void Arma::recargar(){
    this->municiones = municiones_iniciales;
}

void Arma::soltar() {
    this->agarrada = false;
    this->soltada = true;
}

bool Arma::puede_agarrarse() { return !this->soltada; }

bool Arma::tiene_retroceso() { return this->retroceso; }

int Arma::obtener_alcance() { return this->alcance; }

posicion_t Arma::obtener_posicion_inicial() { return posicion_spawn; }

int Arma::municiones_restantes() { return this->municiones; }

bool Arma::en_uso() { return this->agarrada; }

void Arma::eliminar_bala(const int& indice){
    Municion* auxiliar = balas[indice];
    balas.erase(balas.begin() + indice);
    delete auxiliar;
    for (int i = indice; i < (int)balas.size(); i++){
        balas[i]->nro_bala -= 1;
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
        size_t i = 0;
        while (i < balas.size()) {
            if (balas[i]->fuera_de_rango(mapa)) {
                eliminar_bala(i);
                no_borre_ninguno = false;
                break;
            } else {
                if (balas[i]->avanzar(mapa))
                    i++;
                else {
                    eliminar_bala(i);
                    no_borre_ninguno = false;
                    break;
                }
            }
        }
    }
}

void Arma::control_atributos(Mapa& mapa){
    chequeo_balas(mapa);
}

Arma::~Arma() {
    for (Municion* m: balas) {
        delete m;
    }
    balas.clear();
    municiones = 0;
    soltada = true;
}
