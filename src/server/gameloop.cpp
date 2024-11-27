#include "server/gameloop.h"

#include <algorithm>

#include <time.h>

#include "ak47.h"
#include "config_juego.h"
#include "magnum.h"
#include "p_p_laser.h"
#include "shotgun.h"
#include "sniper.h"
#include "spawn_place.h"

#define MENOS_UNO -1
#define CERO 0
#define UNO 1
#define DOS 2
#define TRES 3
#define CINCO 5
#define DIEZ 10
#define CIEN 100
#define MIL 1000

#define INGAME 1
#define CADA_5_RONDAS 2
#define GANADOR 3
#define CANTIDAD_ITERACIONES_TABLERO 70
#define CANT_IDS_ARMAS 5
#define ID_SPAWN_CASCO 1
#define ID_SPAWN_ARMADURA 2
#define ID_SPAWN_ARMA 3

#define VALOR_ENTRE_RONDAS 0xFC

Gameloop::Gameloop(Queue<comando_t>& q, ListaQueues& l):
        queue(q), juego_activo(true), queues_clientes(l), mapa(), rondas_jugadas(CERO), ultimo_id_agregado(CERO) {
    mapa.inicializar_puntos_spawn(puntos_spawn);
    inicializar_cajas();
}

void Gameloop::inicializar_cajas() {
    for (int i = CERO; i < TRES; i++) {
        cajas.push_back(Caja(mapa.posicion_caja(i), i));
        std::vector<int> bloque_caja = mapa.posicion_en_mapa(cajas[i].posicion);
        mapa.mapa[bloque_caja[UNO]][bloque_caja[CERO]] = TRES;
    }
}

void Gameloop::chequear_nuevos_jugadores() {
    size_t cantidad_jugadores = jugadores.size();
    size_t cantidad_queues = queues_clientes.get_size();
    if (cantidad_jugadores == cantidad_queues)
        return;

    if (cantidad_jugadores < cantidad_queues) {
        for (size_t i = cantidad_jugadores; i < cantidad_queues; i++) {
            jugadores.push_back(new Pato(ultimo_id_agregado, mapa));
            ultimo_id_agregado++;
            jugadores_vivos.push_back(true);
        }
    }
}

void Gameloop::chequear_jugadores_desconectados(){
    size_t cantidad_jugadores = jugadores.size();
    for(size_t i = 0; i < cantidad_jugadores; i++){
        int id = jugadores[i]->id_jugador;
        if (!queues_clientes.encontrar_cliente(id)){
            Pato* pato = jugadores[i];
            jugadores.erase(jugadores.begin() + i);
            delete pato;
            jugadores_vivos.erase(jugadores_vivos.begin() + i);
            break;
        }
    }
}

bool Gameloop::hay_ganador() {
    if (jugadores.size() < DOS)
        return false;

    size_t vivos = jugadores.size();
    for (auto pato: jugadores_vivos) {
        if (!pato)
            vivos -= UNO;
    }

    return vivos == UNO;
}

void Gameloop::actualizar_estado_jugadores() {
    for (Pato* p: jugadores) {
        p->control_pre_comando(this->mapa, balas_volando);
        if (!p->vivo) {
            if (jugadores_vivos[p->id_jugador]) {
                jugadores_vivos[p->id_jugador] = false;
            }
        }
    }
}

void Gameloop::enviar_estado_juego(bool ingame) {
    EstadoJuego estado_actual(mapa.id_mapa);
    if (jugadores.empty()) {
        // Si no hay jugadores, no envia nada.
    } else {
        for (Pato* p: jugadores) {
            estado_actual.agregar_info_pato(p);
            if (p->arma_equipada) {
                for (Municion m: p->arma_equipada->balas) {
                    estado_actual.agregar_bala(m);
                }
            }
        }
    }

    for (Municion m: balas_volando) {
        estado_actual.agregar_bala(m);
    }

    for (InformacionArma a: armas_tiradas) {
        estado_actual.agregar_arma(a);
    }

    for (posicion_t pos: cascos_tirados) {
        estado_actual.agregar_casco(pos);
    }

    for (posicion_t pos: armaduras_tiradas) {
        estado_actual.agregar_armadura(pos);
    }

    for (size_t i = CERO; i < cajas.size(); i++) {
        if (!cajas[i].destruida)
            estado_actual.agregar_caja(cajas[i]);
    }

    estado_actual.rondas_jugadas = this->rondas_jugadas;
    estado_actual.ingame = ingame;
    if (!ingame) {
        if (fin_partida()) {
            int maximo_ganador = MENOS_UNO;
            int rondas_ganadas = MENOS_UNO;
            for (Pato* p: jugadores) {
                if (p->rondas_ganadas > rondas_ganadas) {
                    rondas_ganadas = p->rondas_ganadas;
                    maximo_ganador = p->id_jugador;
                }
            }

            estado_actual.definir_ganador(maximo_ganador);
        }
    }

    queues_clientes.broadcast(estado_actual);
}

void Gameloop::actualizar_balas_disparadas() {
    for (Pato* p: jugadores) {
        if (p->arma_equipada) {
            p->arma_equipada->control_atributos(mapa);
        }
    }
}

void Gameloop::chequear_posiciones() {
    for (Pato* p: jugadores) {
        if (p->arma_equipada && !p->arma_equipada->balas.empty()) {
            for (Municion m: p->arma_equipada->balas) {
                for (Pato* otro: jugadores) {
                    if (p->id_jugador != otro->id_jugador) {
                        if (mapa.posicion_en_mapa(otro->posicion) ==
                            mapa.posicion_en_mapa(m.posicion_actual)) {
                            if (m.posicion_actual.misma_posicion(otro->posicion)) {
                                otro->recibir_disparo();
                                p->arma_equipada->eliminar_bala(m.nro_bala);
                            }
                        }
                    }
                }

                for (size_t i = CERO; i < cajas.size(); i++) {
                    if (!cajas[i].destruida) {
                        if (mapa.posicion_en_mapa(m.posicion_actual) ==
                            mapa.posicion_en_mapa(cajas[i].posicion)) {
                            if (m.posicion_actual.hit_caja(cajas[i].posicion, m.id_arma)) {
                                cajas[i].recibir_disparo();
                                p->arma_equipada->eliminar_bala(m.nro_bala);
                                if (cajas[i].destruida) {
                                    posicion_t posicion_caja = cajas[i].posicion;
                                    int arma = cajas[i].destruir();
                                    if (arma == UNO) {
                                        cascos_tirados.push_back(posicion_caja);
                                    } else if (arma == DOS) {
                                        armaduras_tiradas.push_back(posicion_caja);
                                    } else if (arma == TRES) {
                                        int id_arma = rand() % CANT_IDS_ARMAS + UNO;
                                        armas_tiradas.push_back(
                                                InformacionArma(id_arma, posicion_caja));
                                    }

                                    std::vector<int> caja_en_mapa =
                                            mapa.posicion_en_mapa(cajas[i].posicion);
                                    mapa.mapa[caja_en_mapa[UNO]][caja_en_mapa[CERO]] = CERO;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    size_t i = CERO;
    while (i < balas_volando.size()) {
        for (Pato* p: jugadores) {
            if (mapa.posicion_en_mapa(balas_volando[i].posicion_actual) ==
                mapa.posicion_en_mapa(p->posicion)) {
                if (balas_volando[i].posicion_actual.misma_posicion(p->posicion)) {
                    p->recibir_disparo();
                    balas_volando.erase(balas_volando.begin() + i);
                    break;
                }
            }
        }

        for (size_t i = CERO; i < cajas.size(); i++) {
            if (mapa.posicion_en_mapa(balas_volando[i].posicion_actual) ==
                mapa.posicion_en_mapa(cajas[i].posicion)) {
                if (balas_volando[i].posicion_actual.hit_caja(cajas[i].posicion, balas_volando[i].id_arma)) {
                    cajas[i].recibir_disparo();
                    if (cajas[i].destruida) {
                        int spawn = cajas[i].destruir();
                        if (spawn == ID_SPAWN_CASCO) {
                            cascos_tirados.push_back(cajas[i].posicion);
                        } else if (spawn == ID_SPAWN_ARMADURA) {
                            armaduras_tiradas.push_back(cajas[i].posicion);
                        } else if (spawn == ID_SPAWN_ARMA) {
                            int id_arma = (rand() % CANT_IDS_ARMAS) + UNO;
                            armas_tiradas.push_back(InformacionArma(id_arma, cajas[i].posicion));
                        }

                        std::vector<int> caja_en_mapa = mapa.posicion_en_mapa(cajas[i].posicion);
                        mapa.mapa[caja_en_mapa[UNO]][caja_en_mapa[CERO]] = CERO;
                    }

                    balas_volando.erase(balas_volando.begin() + i);
                    break;
                }
            }
        }

        i++;
    }
}

void Gameloop::loop_juego() {
    chequear_nuevos_jugadores();
    chequear_jugadores_desconectados();
    if (!jugadores.empty()) {
        chequear_posiciones();
        actualizar_estado_jugadores();
        actualizar_balas_disparadas();
        spawnear_elementos();
        control_balas();
        comando_t cmd;
        if (queue.try_pop(cmd)) {
            if (jugadores.size() > UNO) {
                for (Pato* p: jugadores) {
                    if (cmd.id_cliente == p->id_jugador) {
                        p->realizar_accion(cmd.accion, mapa, armas_tiradas, cascos_tirados,
                                           armaduras_tiradas, puntos_spawn, balas_volando, cajas);
                    }
                }
            }
        }
    }

    enviar_estado_juego(INGAME);
}

void Gameloop::control_balas() {
    bool no_borre_ninguno = false;
    while (!no_borre_ninguno) {
        no_borre_ninguno = true;
        size_t i = CERO;
        while (i < balas_volando.size()) {
            if (balas_volando[i].fuera_de_rango(mapa)) {
                balas_volando.erase(balas_volando.begin() + i);
                no_borre_ninguno = false;
                break;
            } else {
                if (balas_volando[i].avanzar(mapa)) {
                    i++;
                } else {
                    balas_volando.erase(balas_volando.begin() + i);
                    no_borre_ninguno = false;
                    break;
                }
            }
        }
    }
}

bool Gameloop::fin_partida() {
    if (rondas_jugadas % CINCO != CERO)
        return false;
    bool ganador_unico = false;
    int maximas_ganadas = CERO;
    for (Pato* p: jugadores) {
        if (p->rondas_ganadas > maximas_ganadas) {
            maximas_ganadas = p->rondas_ganadas;
            ganador_unico = true;
        } else if (p->rondas_ganadas == maximas_ganadas) {
            ganador_unico = false;
        }
    }

    if (maximas_ganadas < DIEZ)
        ganador_unico = false;
    return ganador_unico;
}

void Gameloop::resetear_jugadores() {
    for (size_t i = CERO; i < jugadores_vivos.size(); i++) {
        jugadores_vivos[i] = true;
    }

    for (Pato* p: jugadores) {
        p->resetear(mapa);
    }
}

void Gameloop::jugar_ronda() {
    while (!hay_ganador()) {
        auto t1 = std::chrono::steady_clock::now();
        unsigned long frame_count = CERO;

        // Definir el intervalo de tiempo ideal para cada frame en milisegundos
        int ms_per_frame = MIL / ConfigJuego::FPS;
        loop_juego();

        // Calcular el tiempo transcurrido desde el inicio de este frame
        auto t2 = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        // Dormir el tiempo restante para completar el intervalo de 30 ConfigJuego::FPS
        if (elapsed < ms_per_frame) {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms_per_frame - elapsed));
        }

        // Actualizar `t1` sumando un intervalo fijo para mantener la consistencia en el tiempo de
        // frames
        t1 += std::chrono::milliseconds(ms_per_frame);
        frame_count++;
    }

    for (size_t i = CERO; i < jugadores_vivos.size(); i++) {
        if (jugadores_vivos[i]) {
            jugadores[i]->rondas_ganadas += UNO;
        }
    }
}

void Gameloop::resetear_atributos() {
    mapa.resetear();
    cajas.clear();
    inicializar_cajas();
    puntos_spawn.clear();
    mapa.inicializar_puntos_spawn(puntos_spawn);
    cascos_tirados.clear();
    armaduras_tiradas.clear();
    armas_tiradas.clear();
    balas_volando.clear();
    resetear_jugadores();
}

void Gameloop::enviar_tablero_rondas() {
    for (int i = CERO; i < CANTIDAD_ITERACIONES_TABLERO; i++) {
        auto t1 = std::chrono::steady_clock::now();
        unsigned long frame_count = CERO;
        int ms_per_frame = MIL / ConfigJuego::FPS;
        enviar_estado_juego(false);
        auto t2 = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        if (elapsed < ms_per_frame) {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms_per_frame - elapsed));
        }

        t1 += std::chrono::milliseconds(ms_per_frame);
        frame_count++;
    }
}

void Gameloop::run() {
    enviar_estado_juego(true);
    while (juego_activo && !fin_partida()) {
        jugar_ronda();
        rondas_jugadas += UNO;
        if ((rondas_jugadas % CINCO) == CERO) {
            enviar_tablero_rondas();
        } else {
            enviar_estado_juego(false);
        }

        resetear_atributos();
    }

    enviar_estado_juego(false);
    this->juego_activo = false;
}

void Gameloop::spawnear_elementos() {
    for (size_t i = CERO; i < puntos_spawn.size(); i++) {
        bool spawn = puntos_spawn[i].spawnear();
        if (spawn) {
            if (puntos_spawn[i].contenido == ID_SPAWN_CASCO) {
                cascos_tirados.push_back(posicion_t(puntos_spawn[i].posicion));
            } else if (puntos_spawn[i].contenido == ID_SPAWN_ARMADURA) {
                armaduras_tiradas.push_back(posicion_t(puntos_spawn[i].posicion));
            } else {
                int arma = (rand() % CANT_IDS_ARMAS + UNO);
                InformacionArma arma_nueva(arma, puntos_spawn[i].posicion);
                armas_tiradas.push_back(arma_nueva);
            }
        }
    }
}

Gameloop::~Gameloop() {
    juego_activo = false;
    for (size_t i = CERO; i < jugadores.size(); i++) {
        if (jugadores[i]) {
            delete jugadores[i];
        }
    }
    puntos_spawn.clear();
    armas_tiradas.clear();
    jugadores.clear();
}
