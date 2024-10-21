#include "pato.h"

#include <iostream>
#include <string>

Pato::Pato(int id):
        id_jugador(id),
        posicion(0, 0),
        vivo(true),
        posee_arma(false),
        posee_armadura(false),
        posee_casco(false),
        agachado(true),
        orientacion(orientacion_e::DERECHA) {}

posicion_t Pato::obtener_posicion() { return this->posicion; }

bool Pato::mover_derecha() {
    this->posicion.coordenada_x += 1;
    return true;
}

bool Pato::mover_izquierda() {
    this->posicion.coordenada_x -= 1;
    return true;
}

void Pato::saltar() {
    this->posicion.coordenada_y += 5;  // VER
}

void Pato::aletear() {
    if (this->posicion.coordenada_y > 0) {
        this->posicion.coordenada_y += 1;
    }
}

void Pato::caer() { this->posicion.coordenada_y -= 1; }

bool Pato::tiene_arma() { return this->posee_arma; }

bool Pato::tiene_armadura() { return this->posee_armadura; }

bool Pato::tiene_casco() { return this->posee_casco; }

orientacion_e Pato::obtener_orientacion() { return this->orientacion; }

void Pato::cambiar_orientacion(orientacion_e nueva_orientacion) {
    this->orientacion = nueva_orientacion;
}

bool Pato::agarrar_arma() {
    this->posee_arma = true;
    return true;
}

void Pato::soltar_arma() { this->posee_arma = false; }

bool Pato::esta_vivo() { return this->vivo; }

bool Pato::agarrar_armadura() {
    this->posee_armadura = true;
    return true;
}

bool Pato::agarrar_casco() {
    this->posee_casco = true;
    return true;
}

bool Pato::disparar() {
    if (arma_equipada) {
        arma_equipada->disparar();
        return true;
    } else {
        return false;
    }
}

void Pato::agacharse() { this->agachado = true; }
