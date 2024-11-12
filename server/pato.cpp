#include "server/pato.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ak47.h"

#define FPS 30

#define MOVER_DERECHA 0.5
#define MOVER_IZQUIERDA -0.5
#define SALTO_Y_CAIDA 0.33

#define COMANDO_DERECHA 1
#define COMANDO_IZQUIERDA 2
#define COMANDO_AGACHARSE 3
#define COMANDO_MIRAR_HACIA_ARRIBA 4
#define COMANDO_SALTO_Y_ALETEO 5
#define COMANDO_DISPARO 6
#define COMANDO_AGARRAR 7

Pato::Pato(int id):
        id_jugador(id),
        posicion(5, 89),
        vivo(true),
        posee_arma(true),
        posee_armadura(false),
        posee_casco(false),
        orientacion(DERECHA),
        arma_equipada(new AK47(posicion)),
        estado_actual(PARADO),
        iteraciones_subiendo(0),
        iteraciones_agachado(0),
        iteraciones_desde_aleteo(FPS/2) {}

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
    return (mapa.mapa[bloque_y][bloque_x + lado] == 1);
}

bool Pato::chequeo_movimiento(Mapa& mapa, const orientacion_e& direccion) {
    bool se_movio;
    if (!mapa.borde_bloque(this->posicion, direccion)) {
        se_movio = true;
    } else {
        std::cout << "Cambio de bloque\n";
        se_movio = !(Pato::buscar_pared(mapa, direccion, this->posicion));
        std::cout << (se_movio ? "Cruzo" : "No cruzo") << std::endl;
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
        float pasos = derecha ? MOVER_DERECHA : MOVER_IZQUIERDA;
        this->posicion.coordenada_x += pasos;
        if (estado_actual != SALTANDO && estado_actual != CAYENDO){
            estado_actual = CAMINANDO;
        }
    }
    return se_movio;
}

void Pato::saltar() {
    std::cout << "Empiezo salto\n";
    estado_actual = SALTANDO;
    this->posicion.coordenada_y -= SALTO_Y_CAIDA;
    this->iteraciones_subiendo = 1;
    std::cout << "Posicion ni bien salto: " << this->posicion.to_string();
}

void Pato::aletear() {
    if (iteraciones_desde_aleteo < FPS/2){
        return;
    }
    if (estado_actual == CAYENDO) {
        estado_actual = ALETEANDO;
        std::cout << "Aleteando. ";
        this->posicion.coordenada_y -= 1.5;
        std::cout << "Posicion: " << this->posicion.to_string();
        iteraciones_desde_aleteo = 0;
    }
}

void Pato::caer(Mapa& mapa) {
    if (!this->vivo)
        return;
    if (this->posicion.coordenada_y >= (mapa.alto * TILE_A_METRO) - 1) {
        std::cout << "Me fui del mapa\n";
        this->vivo = false;
        return;
    }
    // si no esta en el piso del bloque, tiene que caer si o si
    if (!mapa.piso_bloque(this->posicion)) {
        this->posicion.coordenada_y += SALTO_Y_CAIDA;
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
        if (mapa.mapa[tile_y][tile_x] == 0) {
            // tecnicamente estoy en un bloque que no tiene piso abajo, pero el cuerpo del pato no
            // paso por completo a ese nuevo bloque entonces no debe caer

            bool piso_a_la_izquierda = (tile_x > 0 && (mapa.mapa[tile_y][tile_x - 1] == 1));
            bool piso_a_la_derecha = (tile_x < mapa.largo && (mapa.mapa[tile_y][tile_x + 1] == 1));
            
            if (piso_a_la_derecha || piso_a_la_izquierda){
                
                bool yendo_derecha = this->orientacion == DERECHA && ((int)this->posicion.coordenada_x % TILE_A_METRO < (TILE_A_METRO / 2));
                bool yendo_izquierda = this->orientacion == IZQUIERDA && ((int)this->posicion.coordenada_x % TILE_A_METRO >= (TILE_A_METRO / 2)); 
                if (yendo_derecha || yendo_izquierda){
                    estado_actual = PARADO;
                    return;
                }
            }
            this->posicion.coordenada_y += SALTO_Y_CAIDA;
            estado_actual = CAYENDO;

            // el bloque de abajo en el que estoy tiene su piso a "mitad del bloque" (el piso no
            // esta alineado con el cambio de bloques)
        } else if (mapa.mapa[tile_y-1][tile_x] == 2) {
            int posicion_en_bloque = (int)posicion.coordenada_y % TILE_A_METRO;
            int mitad_bloque = TILE_A_METRO / 2;
            std::cout << posicion_en_bloque << std::endl;
            if (posicion_en_bloque < mitad_bloque) {
                posicion.coordenada_y += SALTO_Y_CAIDA;
                estado_actual = CAYENDO;
            }
        } else {
            estado_actual = PARADO;
        }
    }
    if (this->posicion.coordenada_y > mapa.alto * TILE_A_METRO)
        this->vivo = false;

    if (estado_actual == CAYENDO) {
        std::cout << "Cayendo. Posicion actual: " << this->posicion.to_string();
    }
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

bool Pato::disparar(Mapa& mapa) {
    if (arma_equipada) {
        return arma_equipada->disparar(this->orientacion, mapa);
    } else {
        return false;
    }
}

void Pato::agacharse() { 
    estado_actual = AGACHADO;
    iteraciones_agachado = 1; 
}

void Pato::chequear_estado() {
    switch (estado_actual) {
        case AGACHADO:
            if (iteraciones_agachado >= FPS){
                estado_actual = PARADO;
            } else {
                iteraciones_agachado += 1;
            }
            break;

        case SALTANDO:
            if (iteraciones_subiendo <
                (3*TILE_A_METRO /
                 SALTO_Y_CAIDA) + 1) {  // Como los tiles miden 10 y sube de a 2 metros, se
                                    // necesitan 5 iteraciones para realizar un salto
                // if (mapa.techo_bloque(this->posicion)){
                //     std::vector<int> pos = mapa.posicion_en_mapa(this->posicion);
                //     if (mapa.mapa[pos[1]-1][pos[0]] != 0){
                //         estado_actual = CAYENDO;
                //         iteraciones_subiendo = 0;
                //     }
                // } else {
                    posicion.coordenada_y -= SALTO_Y_CAIDA;
                    iteraciones_subiendo += 1;
                    std::cout << "Subiendo. Posicion: " << this->posicion.to_string();
                // }
            } else {
                estado_actual = CAYENDO;
                iteraciones_subiendo = 0;
            }
            break;

        case ALETEANDO:
            this->posicion.coordenada_y -= 1.5;
            estado_actual = CAYENDO;
            break;

        case CAMINANDO:
            estado_actual = PARADO;
            break;
        default:
            break;
    }
}

void Pato::control_pre_comando(Mapa& mapa) {
    iteraciones_desde_aleteo += 1;
    if (this->posicion.coordenada_x > mapa.largo * TILE_A_METRO ||
        this->posicion.coordenada_y > mapa.alto * TILE_A_METRO) {
        this->vivo = false;  // Si esta fuera del mapa, tiene que morir
    }
    if (orientacion == ARRIBA) {
        cambiar_orientacion(DERECHA);
    }
    if (estado_actual != SALTANDO) {
        caer(mapa);
    }
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
        posee_casco = false;  // Si le pegan un disparo, pierde el casco pero sigue vivo.
        return;
    }
    if (posee_armadura) {
        posee_armadura = false;  // Si le pegan un disparo, pierde el armadura pero sigue vivo.
    }
    vivo = false;  // Si llego a este punto, no tenia ni casco ni armadura, entonces muere.
}

std::string orientacion_texto(const orientacion_e& direccion) {
    if (direccion == DERECHA)
        return "Derecha\n";
    if (direccion == IZQUIERDA)
        return "Izquierda\n";
    return "Arriba\n";
}

void Pato::realizar_accion(int accion, Mapa& mapa) {
    switch (accion) {
        case COMANDO_MIRAR_HACIA_ARRIBA:
            std::cout << "Mirando para: " << orientacion_texto(this->orientacion);
            this->cambiar_orientacion(orientacion_e::ARRIBA);
            std::cout << "Mirando para: " << orientacion_texto(this->orientacion);
            break;
        case COMANDO_AGACHARSE:
            std::cout << "Estoy parado\n";
            agacharse();
            if (this->estado_actual == AGACHADO)
                std::cout << "Estoy agachado\n";
            break;
        case COMANDO_SALTO_Y_ALETEO:
            if (estado_actual == PARADO) {
                saltar();
            } else {
                aletear();
            }
            break;
        case COMANDO_DISPARO:
            if (arma_equipada) {
                if (disparar(mapa)) {
                    std::cout << "Disparo\n";
                    if (arma_equipada->tiene_retroceso()) {
                        this->posicion.coordenada_x += MOVER_IZQUIERDA;
                    }
                } else {
                    std::cout << "Estoy aca\n";
                    delete arma_equipada;
                    std::cout << "No tiene mas balas\n";
                }
            } else {
                std::cout << "No puedo disparar, no tengo arma bro\n";
            }
            break;
        case COMANDO_AGARRAR:
            // logica para ver si el arma/casco/armadura esta en la misma posicion para
            // agarrar
            break;
        default:
            orientacion_e sentido = (accion == COMANDO_DERECHA) ? DERECHA : IZQUIERDA;
            std::cout << "Posicion vieja: " << this->posicion.to_string();
            std::cout << "Mirando para: " << orientacion_texto(this->orientacion);
            if (mover(mapa, sentido)) {
                std::cout << "Posicion nueva: " << this->posicion.to_string();
                std::cout << "Mirando para: " << orientacion_texto(this->orientacion);
            }
            break;
    }
}

Pato::~Pato() {
    if (arma_equipada)
        delete arma_equipada;
}
