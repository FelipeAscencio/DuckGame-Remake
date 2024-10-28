#include "pato.h"

#include <iostream>
#include <string>

#define MOVER_DERECHA 2
#define MOVER_IZQUIERDA -2
#define SALTO_Y_CAIDA 2

#define COMANDO_DERECHA 1
#define COMANDO_IZQUIERDA 2
#define COMANDO_AGACHARSE 3
#define COMANDO_MIRAR_HACIA_ARRIBA 4
#define COMANDO_SALTO_Y_ALETEO 5
#define COMANDO_DISPARO_Y_PICKUP 6

Pato::Pato(int id):
        id_jugador(id),
        posicion(0, 0),
        vivo(true),
        posee_arma(false),
        posee_armadura(false),
        posee_casco(false),
        orientacion(DERECHA),
        arma_equipada(nullptr),
        estado_actual(PARADO),
        iteraciones_subiendo(0) {}

posicion_t Pato::obtener_posicion() { return this->posicion; }

bool Pato::chequeo_bordes(Mapa& mapa, const orientacion_e& direccion) {
    bool se_movio;
    if (!mapa.borde_bloque(this->posicion, direccion)) {
        se_movio = true;
    } else {
        std::vector<int> tile_actual = mapa.posicion_en_mapa(this->posicion);
        int bloque_x = tile_actual[0];
        int bloque_y = tile_actual[1];
        int lado = (direccion == DERECHA) ? 1 : -1;
        se_movio = (mapa.mapa[bloque_x + lado][bloque_y] == 0);
    }
    return se_movio;
}

bool Pato::mover(Mapa& mapa, const orientacion_e& direccion) {
    if (direccion != this->orientacion)
        cambiar_orientacion(direccion);
    bool se_movio;

    bool fuera_del_mapa_por_derecha =
            (this->posicion.coordenada_x > (mapa.largo * TILE_A_METRO) - MOVER_DERECHA) &&
            (direccion == DERECHA);
    bool fuera_del_mapa_por_izquierda =
            (this->posicion.coordenada_x < -MOVER_IZQUIERDA) && (direccion == IZQUIERDA);

    if (fuera_del_mapa_por_derecha || fuera_del_mapa_por_izquierda) {
        this->vivo = false;  // se va del mapa, muere
        se_movio = true;
    } else {
        se_movio = chequeo_bordes(mapa, direccion);
    }
    if (se_movio) {
        int pasos_caminados = (direccion == DERECHA) ? MOVER_DERECHA : MOVER_IZQUIERDA;
        this->posicion.coordenada_x += pasos_caminados;
    }
    return se_movio;
}

void Pato::saltar() {
    estado_actual = SALTANDO;
    this->posicion.coordenada_y -= SALTO_Y_CAIDA;
    this->iteraciones_subiendo = 1;
}

void Pato::aletear() {
    if (estado_actual == CAYENDO) {
        estado_actual = ALETEANDO;
        this->posicion.coordenada_y -= SALTO_Y_CAIDA / 2;
    }
}

void Pato::caer(Mapa& mapa) {
    if (!mapa.piso_bloque(this->posicion)) {
        if (this->posicion.coordenada_y % TILE_A_METRO >= SALTO_Y_CAIDA) {
            this->posicion.coordenada_y += SALTO_Y_CAIDA;  // si esta a 2 metros o mas, tiene que
                                                           // caer 2 metros por segundo por gravedad
        } else {
            this->posicion.coordenada_y =
                    SALTO_Y_CAIDA / 2;  // si esta 1 metro por encima del piso, tiene que caer solo
                                        // un metro, no mas.
        }
        estado_actual = CAYENDO;
    } else {
        std::vector<int> tile_actual = mapa.posicion_en_mapa(this->posicion);
        int tile_x = tile_actual[0];
        int tile_y = tile_actual[1] + 1;
        if (tile_y > mapa.alto) {
            posicion.coordenada_y += SALTO_Y_CAIDA;
            return;
        }
        if (mapa.mapa[tile_x][tile_y] == 0) {
            if (tile_x > 0 && mapa.mapa[tile_x - 1][tile_y] == 1) {
                if ((posicion.coordenada_x % TILE_A_METRO <= MOVER_DERECHA) ||
                    posicion.coordenada_x % TILE_A_METRO >= (TILE_A_METRO + MOVER_IZQUIERDA)) {
                    estado_actual = PARADO;
                    return;  // ya pase de bloque en el mapa pero el pato todavia tiene una parte
                             // del cuerpo en el borde anterior
                }
            }
            this->posicion.coordenada_y += SALTO_Y_CAIDA;
            estado_actual = CAYENDO;
        } else if (mapa.mapa[tile_x][tile_y] == 2) {
            int posicion_en_bloque = posicion.coordenada_y % TILE_A_METRO;
            int mitad_bloque = TILE_A_METRO / 2;
            if (posicion_en_bloque < mitad_bloque) {
                posicion.coordenada_y += (mitad_bloque - posicion_en_bloque > SALTO_Y_CAIDA) ?
                                                 SALTO_Y_CAIDA :
                                                 (mitad_bloque - posicion_en_bloque);
                estado_actual = CAYENDO;
            }
        } else {
            estado_actual = PARADO;
        }
    }
    if (this->posicion.coordenada_y > mapa.largo)
        this->vivo = false;
}

bool Pato::tiene_arma() { return this->posee_arma; }

bool Pato::tiene_armadura() { return this->posee_armadura; }

bool Pato::tiene_casco() { return this->posee_casco; }

orientacion_e Pato::obtener_orientacion() { return this->orientacion; }

void Pato::cambiar_orientacion(orientacion_e nueva_orientacion) {
    this->orientacion = nueva_orientacion;
}

bool Pato::agarrar_arma(Arma* arma) {
    this->posee_arma = true;
    this->arma_equipada = arma;
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
        arma_equipada->disparar(this->orientacion);
        return true;
    } else {
        return false;
    }
}

void Pato::agacharse() { estado_actual = AGACHADO; }

void Pato::chequear_estado() {
    switch (estado_actual) {
        case AGACHADO:
            estado_actual = PARADO;
            break;

        case SALTANDO:
            if (iteraciones_subiendo <
                (TILE_A_METRO /
                 SALTO_Y_CAIDA)) {  // Como los tiles miden 10 y sube de a 2 metros, se
                                    // necesitan 5 iteraciones para realizar un salto
                posicion.coordenada_y -= SALTO_Y_CAIDA;
                iteraciones_subiendo += 1;
            } else {
                estado_actual = CAYENDO;
                iteraciones_subiendo = 0;
            }
            break;

        case ALETEANDO:
            estado_actual = CAYENDO;
            break;

        default:
            break;
    }
}

void Pato::control_pre_comando(Mapa& mapa) {
    if (posicion.coordenada_x > mapa.alto || posicion.coordenada_x > mapa.largo * TILE_A_METRO) {
        this->vivo = false;  // Si esta fuera del mapa, tiene que morir
    }
    if (orientacion == ARRIBA) {
        cambiar_orientacion(DERECHA);
    }
    if (estado_actual != SALTANDO)
        caer(mapa);
    chequear_estado();
    if (posee_arma) {
        if (this->arma_equipada->municiones_restantes() == 0) {
            delete this->arma_equipada;
            arma_equipada = nullptr;
            posee_arma = false;
        }
    }
}

void Pato::recibir_disparo() {
    if (posee_casco) {
        posee_casco = false;  // si le pegan un disparo, pierde el casco pero sigue vivo
        return;
    }
    if (posee_armadura) {
        posee_armadura = false;  // si le pegan un disparo, pierde el armadura pero sigue vivo
    }
    vivo = false;  // si llego a este punto, no tenia ni casco ni armadura, entonces muere
}

void Pato::realizar_accion(int accion, Mapa& mapa) {
    switch (accion) {
        case COMANDO_MIRAR_HACIA_ARRIBA:
            cambiar_orientacion(ARRIBA);
            break;
        case COMANDO_AGACHARSE:
            agacharse();
            break;
        case COMANDO_SALTO_Y_ALETEO:
            if (estado_actual == PARADO) {
                saltar();
            } else {
                aletear();
            }
            break;
        case COMANDO_DISPARO_Y_PICKUP:
            if (arma_equipada) {
                disparar();
            } else {
                // logica para ver si el arma/casco/armadura esta en la misma posicion para agarrar
            }
            break;
        default:
            orientacion_e sentido = (accion == COMANDO_DERECHA) ? DERECHA : IZQUIERDA;
            mover(mapa, sentido);
            break;
    }
}

Pato::~Pato() {}
