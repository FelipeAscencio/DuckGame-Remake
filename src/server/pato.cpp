#include "server/pato.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ak47.h"
#include "magnum.h"
#include "p_p_laser.h"
#include "shotgun.h"
#include "sniper.h"

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
#define CUAK 8
#define CHEAT_AK 32
#define CHEAT_SG 33
#define CHEAT_MAGNUM 34
#define CHEAT_LASER 35
#define CHEAT_SNIPER 36
#define CHEAT_INMORTALIDAD 37
#define CHEAT_RECARGAR 38
#define CHEAT_ARMADUAR 39
#define CHEAT_CASCO 40

Pato::Pato(int id, Mapa& mapa):
        id_jugador(id),
        posicion(mapa.posicion_inicial(id_jugador)),
        vivo(true),
        posee_arma(false),
        posee_armadura(false),
        posee_casco(false),
        arma_equipada(nullptr),
        estado_actual(PARADO),
        iteraciones_subiendo(0),
        iteraciones_desde_aleteo(FPS / 2),
        inmortal(false),
        sonido(SILENCIO),
        rondas_ganadas(0),
        iteraciones_mirando_para_arriba(0) {
    if (this->posicion.coordenada_x > mapa.largo / 2)
        this->orientacion = IZQUIERDA;
    else
        this->orientacion = DERECHA;
    this->orientacion_anterior = orientacion;
}

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
        se_movio = !(Pato::buscar_pared(mapa, direccion, this->posicion));
    }
    return se_movio;
}

bool Pato::mover(Mapa& mapa, const orientacion_e& direccion, bool disparo) {
    if (!disparo && direccion != this->orientacion)
        cambiar_orientacion(direccion);

    bool se_movio;
    bool derecha = (direccion == DERECHA);

    bool fuera_mapa_por_derecha =
            (posicion.coordenada_x > (mapa.largo * TILE_A_METRO) - MOVER_DERECHA) && (derecha);
    bool fuera_mapa_por_izquierda = (posicion.coordenada_x < -MOVER_IZQUIERDA) && (!derecha);
    if (fuera_mapa_por_derecha || fuera_mapa_por_izquierda) {
        this->vivo = false;  // Jugador que se va del mapa, muere.
        se_movio = true;
    } else {
        se_movio = chequeo_movimiento(mapa, direccion);
    }

    if (se_movio) {
        float pasos = derecha ? MOVER_DERECHA : MOVER_IZQUIERDA;
        this->posicion.coordenada_x += pasos;
        if (this->arma_equipada) {
            this->arma_equipada->posicion_spawn.coordenada_x += pasos;
        }
        if (estado_actual != SALTANDO && estado_actual != CAYENDO) {
            estado_actual = CAMINANDO;
        }
    }
    return se_movio;
}

void Pato::saltar() {
    estado_actual = SALTANDO;
    this->posicion.coordenada_y -= SALTO_Y_CAIDA;
    if (this->arma_equipada) {
        this->arma_equipada->posicion_spawn.coordenada_y -= SALTO_Y_CAIDA;
    }
    this->iteraciones_subiendo = 1;
}

void Pato::aletear() {
    if (iteraciones_desde_aleteo < FPS / 2) {
        return;
    }
    if (estado_actual == CAYENDO) {
        estado_actual = ALETEANDO;
        this->posicion.coordenada_y -= 1.5;
        if (this->arma_equipada) {
            this->arma_equipada->posicion_spawn.coordenada_y -= 1.5;
        }
        iteraciones_desde_aleteo = 0;
    }
}

void Pato::caer(Mapa& mapa) {
    if (!this->vivo)
        return;
    if (this->posicion.coordenada_y >= (mapa.alto * TILE_A_METRO) - 1) {
        this->vivo = false;
        return;
    }

    // Si no esta en el piso del bloque debe caer.
    if (!mapa.piso_bloque(this->posicion)) {
        this->posicion.coordenada_y += SALTO_Y_CAIDA;
        if (this->arma_equipada) {
            this->arma_equipada->posicion_spawn.coordenada_y += SALTO_Y_CAIDA;
        }
        estado_actual = CAYENDO;
    } else {
        std::vector<int> tile_actual = mapa.posicion_en_mapa(this->posicion);
        int tile_x = tile_actual[0];
        int tile_y = tile_actual[1] + 1;
        if (tile_y > mapa.alto) {
            posicion.coordenada_y +=
                    SALTO_Y_CAIDA;  // Como el eje Y aumenta hacia abajo, el chequeo es inverso y
                                    // debemos fijarnos si se paso del alto para ver si se cayo del
                                    // mapa por debajo
            if (this->arma_equipada) {
                this->arma_equipada->posicion_spawn.coordenada_y += SALTO_Y_CAIDA;
            }
            return;
        }

        // Si en el bloque de abajo no hay piso.
        if (mapa.mapa[tile_y][tile_x] == 0) {
            // Yecnicamente esta un bloque que no tiene piso abajo, pero el cuerpo del pato no
            // paso por completo a ese nuevo bloque entonces no debe caer.
            bool piso_a_la_izquierda = (tile_x > 0 && (mapa.mapa[tile_y][tile_x - 1] == 1));
            bool piso_a_la_derecha = (tile_x < mapa.largo && (mapa.mapa[tile_y][tile_x + 1] == 1));
            if (piso_a_la_derecha || piso_a_la_izquierda) {
                bool yendo_derecha =
                        this->orientacion == DERECHA &&
                        ((int)this->posicion.coordenada_x % TILE_A_METRO < (TILE_A_METRO / 2) - 1);
                bool yendo_izquierda =
                        this->orientacion == IZQUIERDA &&
                        ((int)this->posicion.coordenada_x % TILE_A_METRO >= (TILE_A_METRO / 2) - 1);
                if (yendo_derecha || yendo_izquierda) {
                    estado_actual = PARADO;
                    return;
                }
            }

            this->posicion.coordenada_y += SALTO_Y_CAIDA;
            if (this->arma_equipada) {
                this->arma_equipada->posicion_spawn.coordenada_y += SALTO_Y_CAIDA;
            }

            estado_actual = CAYENDO;

            // El bloque de abajo en el que esta tiene su piso a "mitad del bloque" (el piso no
            // esta alineado con el cambio de bloques).
        } else if (mapa.mapa[tile_y - 1][tile_x] == 2) {
            int posicion_en_bloque = (int)posicion.coordenada_y % TILE_A_METRO;
            int mitad_bloque = TILE_A_METRO / 2;
            if (posicion_en_bloque < mitad_bloque) {
                posicion.coordenada_y += SALTO_Y_CAIDA;
                estado_actual = CAYENDO;
                if (this->arma_equipada) {
                    this->arma_equipada->posicion_spawn.coordenada_y += SALTO_Y_CAIDA;
                }
            }
        } else {
            estado_actual = PARADO;
        }
    }
    if (this->posicion.coordenada_y > mapa.alto * TILE_A_METRO)
        this->vivo = false;
}

bool Pato::tiene_arma() { return this->posee_arma; }

bool Pato::tiene_armadura() { return this->posee_armadura; }

bool Pato::tiene_casco() { return this->posee_casco; }

orientacion_e Pato::obtener_orientacion() { return this->orientacion; }

void Pato::cambiar_orientacion(const orientacion_e& nueva_orientacion) {
    this->orientacion = nueva_orientacion;
}

bool Pato::agarrar_arma(Arma* arma) {
    // Aca deberia chequear que esten en la misma posicion.
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
        bool disparo = arma_equipada->disparar(this->orientacion, mapa);
        if (disparo) {
            if (arma_equipada->tiene_retroceso()) {
                if (this->orientacion == DERECHA) {
                    mover(mapa, IZQUIERDA, true);
                } else if (this->orientacion == IZQUIERDA) {
                    mover(mapa, DERECHA, true);
                }
            }
        }
        if (arma_equipada->id_arma == ID_SHOTGUN && arma_equipada->municiones != 0)
            return true;
        else
            return disparo;
    } else {
        return false;
    }
}

void Pato::agacharse() { estado_actual = AGACHADO; }

void Pato::chequear_estado(Mapa& mapa) {
    switch (estado_actual) {
        case AGACHADO:
            estado_actual = PARADO;
            break;

        case SALTANDO:
            if (iteraciones_subiendo <
                (3 * TILE_A_METRO / SALTO_Y_CAIDA) +
                        1) {  // Como los tiles miden 10 y sube de a 2 metros, se
                              // necesitan 5 iteraciones para realizar un salto.
                posicion_t posicion_cabeza_pato(this->posicion.coordenada_x,
                                                this->posicion.coordenada_y - 8);
                std::vector<int> pos_mapa = mapa.posicion_en_mapa(posicion_cabeza_pato);
                if ((mapa.techo_bloque(posicion_cabeza_pato) && pos_mapa[1] == 0)) {
                    estado_actual = CAYENDO;
                    iteraciones_subiendo = 0;
                }
                bool bloque_mas_alto = pos_mapa[1] == 0;
                if ((mapa.techo_bloque(posicion_cabeza_pato) &&
                     mapa.mapa[pos_mapa[1] - !bloque_mas_alto][pos_mapa[0]] == 1)) {
                    estado_actual = CAYENDO;
                    iteraciones_subiendo = 0;
                } else {
                    posicion.coordenada_y -= SALTO_Y_CAIDA;
                    if (this->arma_equipada) {
                        this->arma_equipada->posicion_spawn.coordenada_y -= SALTO_Y_CAIDA;
                    }
                    iteraciones_subiendo += 1;
                }
            } else {
                estado_actual = CAYENDO;
                iteraciones_subiendo = 0;
            }
            break;

        case ALETEANDO:
            this->posicion.coordenada_y -= 1.5;
            if (this->arma_equipada) {
                this->arma_equipada->posicion_spawn.coordenada_y -= 1.5;
            }
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
    if (this->arma_equipada)
        this->posee_arma = true;
    else
        this->posee_arma = false;
    iteraciones_desde_aleteo += 1;
    if (this->posicion.coordenada_x < 0 ||
        this->posicion.coordenada_x > mapa.largo * TILE_A_METRO) {
        this->vivo = false;
        return;
    }
    if (this->posicion.coordenada_y > mapa.alto * TILE_A_METRO) {
        this->vivo = false;  // Si esta fuera del mapa, tiene que morir.
        return;
    }
    if (orientacion == ARRIBA) {
        iteraciones_mirando_para_arriba += 1;
        if (iteraciones_mirando_para_arriba == 20) {
            iteraciones_mirando_para_arriba = 0;
            this->orientacion = orientacion_anterior;
        }
    }
    if (estado_actual != SALTANDO) {
        caer(mapa);
    }
    chequear_estado(mapa);
    if (posee_arma) {
        if (this->arma_equipada->municiones_restantes() == 0) {
            delete this->arma_equipada;
            arma_equipada = nullptr;
            posee_arma = false;
        }
    }
    if (this->sonido != SILENCIO) {
        this->sonido = SILENCIO;
    }
}

void Pato::recibir_disparo() {
    if (posee_casco) {
        posee_casco = false;  // Si le pegan un disparo, pierde el casco pero sigue vivo.
        return;
    }
    if (posee_armadura) {
        posee_armadura = false;  // Si le pegan un disparo, pierde el armadura pero sigue vivo.
        return;
    }
    if (inmortal) {
        return;
    }
    vivo = false;  // Si llego a este punto, no tenia ni casco ni armadura, entonces muere.
}

void Pato::realizar_accion(const int& accion, Mapa& mapa) {
    if (!vivo)
        return;
    switch (accion) {
        case COMANDO_MIRAR_HACIA_ARRIBA:
            orientacion_anterior = orientacion;
            this->cambiar_orientacion(orientacion_e::ARRIBA);
            iteraciones_mirando_para_arriba = 0;
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
        case COMANDO_DISPARO:
            if (arma_equipada) {
                if (disparar(mapa)) {
                    this->sonido = DISPARANDO;
                } else {
                    if (arma_equipada) {
                        delete arma_equipada;
                    }
                }
            }
            break;
        case COMANDO_AGARRAR:
            // Logica para ver si el arma/casco/armadura esta en la misma posicion para
            // agarrar
            break;

        case CUAK:
            this->sonido = HACIENDO_CUAK;
            break;

        case CHEAT_AK:
            if (this->arma_equipada) {
                delete this->arma_equipada;
            }
            this->posee_arma = true;
            this->arma_equipada = new AK47(
                    posicion_t(posicion.coordenada_x, posicion.coordenada_y - TILE_A_METRO / 2));
            break;

        case CHEAT_SG:
            if (this->arma_equipada) {
                delete this->arma_equipada;
            }
            this->posee_arma = true;
            this->arma_equipada = new Shotgun(
                    posicion_t(posicion.coordenada_x, posicion.coordenada_y - TILE_A_METRO / 2));
            break;

        case CHEAT_MAGNUM:
            if (this->arma_equipada) {
                delete this->arma_equipada;
            }
            this->posee_arma = true;
            this->arma_equipada = new Magnum(
                    posicion_t(posicion.coordenada_x, posicion.coordenada_y - TILE_A_METRO / 2));
            break;

        case CHEAT_LASER:
            if (this->arma_equipada) {
                delete this->arma_equipada;
            }
            this->posee_arma = true;
            this->arma_equipada = new PewPewLaser(
                    posicion_t(posicion.coordenada_x, posicion.coordenada_y - TILE_A_METRO / 2));
            break;

        case CHEAT_SNIPER:
            if (this->arma_equipada) {
                delete this->arma_equipada;
            }
            this->posee_arma = true;
            this->arma_equipada = new Sniper(
                    posicion_t(posicion.coordenada_x, posicion.coordenada_y - TILE_A_METRO / 2));
            break;

        case CHEAT_INMORTALIDAD:
            this->inmortal = !this->inmortal;
            break;

        case CHEAT_RECARGAR:
            if (this->arma_equipada) {
                this->arma_equipada->recargar();
            }
            break;

        case CHEAT_CASCO:
            this->posee_casco = !this->posee_casco;
            break;

        case CHEAT_ARMADUAR:
            this->posee_armadura = !this->posee_armadura;
            break;

        default:
            orientacion_e sentido = (accion == COMANDO_DERECHA) ? DERECHA : IZQUIERDA;
            mover(mapa, sentido, false);
            break;
    }
}

Pato::~Pato() {
    if (arma_equipada)
        delete arma_equipada;
}