// Copyright 2024 Axel Zielonka y Felipe Ascensio
#include "server/pato.h"

#include <iostream>
#include <string>
#include <vector>

#define MOVER_DERECHA 2
#define MOVER_IZQUIERDA -2
#define SALTO_Y_CAIDA 2

#define COMANDO_DERECHA 1
#define COMANDO_IZQUIERDA 2
#define COMANDO_AGACHARSE 3
#define COMANDO_MIRAR_HACIA_ARRIBA 4
#define COMANDO_SALTO_Y_ALETEO 5
#define COMANDO_DISPARO_Y_PICKUP 6

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

bool Pato::buscar_pared(Mapa& mapa, const orientacion_e& direccion,
                        const posicion_t& posicion_a_chequear) {
    std::vector<int> tile_actual = mapa.posicion_en_mapa(posicion_a_chequear);
    int bloque_x = tile_actual[0];
    int bloque_y = tile_actual[1];
    int lado = (direccion == DERECHA) ? 1 : -1;
    if (direccion == DERECHA && bloque_x == mapa.largo)
        return false;
    if (direccion == IZQUIERDA && bloque_x == 0)
        return false;
    return (mapa.mapa[bloque_x + lado][bloque_y] == 1);
}

bool Pato::chequeo_movimiento(Mapa& mapa, const orientacion_e& direccion) {
    bool se_movio;
    if (!mapa.borde_bloque(this->posicion, direccion)) {
        se_movio = true;
    } else {
        se_movio = Pato::buscar_pared(mapa, direccion, this->posicion);
    }
    return se_movio;
}

bool Pato::mover(Mapa& mapa, const orientacion_e& direccion) {
    if (direccion != this->orientacion)
        cambiar_orientacion(direccion);

    bool se_movio;
    bool derecha = (direccion == DERECHA);

    bool fuera_mapa_por_derecha =
            (posicion.coordenada_x > (mapa.largo * TILE_A_METRO) - MOVER_DERECHA) && (derecha);
    bool fuera_mapa_por_izquierda = (posicion.coordenada_x < -MOVER_IZQUIERDA) && (!derecha);
    if (fuera_mapa_por_derecha || fuera_mapa_por_izquierda) {
        this->vivo = false;  // se fue del mapa, se muere el jugador
        se_movio = true;
    } else {
        se_movio = chequeo_movimiento(mapa, direccion);
    }

    if (se_movio) {
        int pasos_caminados = derecha ? MOVER_DERECHA : MOVER_IZQUIERDA;
        // si estaba en el metro 1 yendo para la izquierda o en el metro 8 yendo para la derecha, el
        // chequeo anterior no me decia si habia una pared, pero como el movimiento es de a 2
        // metros, tengo que volver a chequear por las dudas
        if (posicion.coordenada_x == TILE_A_METRO - MOVER_DERECHA ||
            posicion.coordenada_x == (-MOVER_IZQUIERDA) / 2) {
            int sentido = derecha ? 1 : -1;
            posicion_t posicion_a_chequear(posicion.coordenada_x + sentido, posicion.coordenada_y);
            if (Pato::buscar_pared(mapa, direccion, posicion_a_chequear)) {
                pasos_caminados /= 2;  // so efectivamente hay una pared, tengo que caminar solo la
                                       // distancia que falta hasta chocar con esa pared
            }
        }
        posicion.coordenada_x += pasos_caminados;
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
    // si no esta en el piso del bloque, tiene que caer si o si
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
            posicion.coordenada_y +=
                    SALTO_Y_CAIDA;  // como el eje Y aumenta hacia abajo, el chequeo es inverso y me
                                    // tengo que fijar si me pase del alto para ver si me caigo del
                                    // mapa por debajo
            return;
        }
        // si en el bloque de abajo no hay piso
        if (mapa.mapa[tile_x][tile_y] == 0) {
            // tecnicamente estoy en un bloque que no tiene piso abajo, pero el cuerpo del pato no
            // paso por completo a ese nuevo bloque entonces no debe caer

            bool piso_a_la_izquierda = (tile_x > 0 && (mapa.mapa[tile_x - 1][tile_y] == 1));
            bool piso_a_la_derecha = (tile_x < mapa.largo && (mapa.mapa[tile_x + 1][tile_y] == 1));
            if (piso_a_la_izquierda || piso_a_la_derecha) {
                if ((posicion.coordenada_x % TILE_A_METRO <= MOVER_DERECHA) ||
                    (posicion.coordenada_x % TILE_A_METRO >= (TILE_A_METRO + MOVER_IZQUIERDA))) {
                    estado_actual = PARADO;
                    return;
                }
            }
            this->posicion.coordenada_y += SALTO_Y_CAIDA;
            estado_actual = CAYENDO;

            // el bloque de abajo en el que estoy tiene su piso a "mitad del bloque" (el piso no
            // esta alineado con el cambio de bloques)
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
    // aca deberia cheqeuar que esten en la misma posicion
    // if (arma_equipada) delete arma_equipada;
    this->posee_arma = true;
    this->arma_equipada = arma;
    return true;
}

void Pato::soltar_arma() {
    // if (arma_equipada) delete arma_equipada;
    this->posee_arma = false;
}

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
