#include "arma.h"

Arma::Arma(const int& id, const std::string& nombre_arma, const int& alcance, const int& municiones,
           bool tiene_retroceso):
        id_arma(id),
        nombre(nombre_arma),
        alcance(alcance),
        municiones(municiones),
        retroceso(tiene_retroceso),
        posicion_spawn(0, 0),
        agarrada(false),
        soltada(false) {}

void Arma::agarrar() { this->agarrada = true; }

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
