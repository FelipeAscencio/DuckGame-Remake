// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef ESTADO_JUEGO_H_
#define ESTADO_JUEGO_H_

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../server/arma.h"
#include "../server/pato.h"
#include "common/estado_fisico.h"
#include "common/orientacion.h"
#include "common/posicion.h"

#define CERO 0
#define ID_GANADOR 0xFD // Valor dummy que indica que no hay un ganador de la ronda actual.

// 'struct' que encapsula la informacion del pato para enviarla en el estado.
struct InformacionPato {
    int id;
    posicion_t posicion;
    bool vivo;
    bool arma;
    int id_arma_equipada; // 0 = no arma, 1 laser, 2 ak, 3 magnum, 4 shotgun, 5 sniper.
    bool casco;
    bool armadura;
    orientacion_e orientacion;
    estado_pato_e estado;
    sonido_e sonido;
    int rondas_ganadas;

    // Constructor del struct con punteros.
    explicit InformacionPato(Pato* p):
            id(p->id_jugador),
            posicion(p->posicion),
            vivo(p->vivo),
            arma(p->posee_arma),
            id_arma_equipada(p->obtener_id_arma()),
            casco(p->posee_casco),
            armadura(p->posee_armadura),
            orientacion(p->orientacion),
            estado(p->estado_actual),
            sonido(p->sonido),
            rondas_ganadas(p->rondas_ganadas) {}

    // Constructor del struct con parametros.
    explicit InformacionPato(const uint8_t& id_pato, const posicion_t& pos, bool esta_vivo,
                             bool tiene_arma, const uint8_t& id_arma, bool tiene_casco,
                             bool tiene_armadura, const orientacion_e& orientacion_pato,
                             const estado_pato_e& estado_pato, const sonido_e& sonido_pato, const uint8_t& rondas):
            id(id_pato),
            posicion(pos),
            vivo(esta_vivo),
            arma(tiene_arma),
            id_arma_equipada(id_arma),
            casco(tiene_casco),
            armadura(tiene_armadura),
            orientacion(orientacion_pato),
            estado(estado_pato),
            sonido(sonido_pato),
            rondas_ganadas(rondas) {}
};

// 'struct' que encapsula la informacion de todas las armas del juego.
struct InformacionArma {
    int id_arma; // 0 = no arma, 1 ak, 2 magnum, 3 laser, 4 shotgun, 5 sniper.
    posicion_t posicion;

    // Primera variante del constructor del struct.
    explicit InformacionArma(Arma* a): id_arma(a->id_arma), posicion(a->posicion_spawn) {}

    // Segunda variante del constructor del struct.
    explicit InformacionArma(uint8_t id, float x, float y): id_arma(id), posicion(x, y) {}

    // Tercera variante del constructor del struct.
    explicit InformacionArma(uint8_t id, posicion_t pos): id_arma(id), posicion(pos) {}
};


// 'struct' que encapsula la informacion de todas las balas del juego.
struct InformacionBala{
    int id_arma; // 0 = no arma, 1 ak, 2 magnum, 3 laser, 4 shotgun, 5 sniper.
    posicion_t pos;
    inclinacion_e inclinacion;
    orientacion_e direccion;

    // Primera variante del constructor del struct.
    explicit InformacionBala(Municion* m): id_arma(m->id_arma), pos(m->posicion_actual), inclinacion(m->inclinacion), direccion(m->sentido){}
    
    // Segundavariante del constructor del struct.
    explicit InformacionBala(const int& id, const posicion_t& posicion, const inclinacion_e& inc, const orientacion_e& sentido): id_arma(id), pos(posicion), inclinacion(inc), direccion(sentido){}
};

// 'struct' que sirve para comparar las 'ID'.
struct MismoID {
    const int id;
    explicit MismoID(int id_buscado): id(id_buscado) {}
    bool operator()(const InformacionPato& i) const { return i.id == id; }
    bool operator()(Pato* p) const { return p->id_jugador == id; }
};

// 'struct' que encapsula el estado actual del juego para enviarlo al 'Cliente'.
struct EstadoJuego {
    int cantidad_jugadores;
    int cantidad_armas;
    int cantidad_balas;
    int cantidad_armaduras;
    int cantidad_cascos;
    int cantidad_cajas;
    int id_ganador;
    int id_mapa;
    std::vector<InformacionPato> info_patos;
    std::vector<InformacionArma> info_armas;
    std::vector<InformacionBala> info_balas;


    // Constructor del struct.
    explicit EstadoJuego():
            cantidad_jugadores(CERO),
            cantidad_armas(CERO),
            cantidad_balas(CERO),
            cantidad_armaduras(CERO),
            cantidad_cascos(CERO),
            cantidad_cajas(CERO), 
            id_ganador(ID_GANADOR),
            id_mapa(0) {}
    
    explicit EstadoJuego(const int& mapa):
            cantidad_jugadores(CERO),
            cantidad_armas(CERO),
            cantidad_balas(CERO),
            cantidad_armaduras(CERO),
            cantidad_cascos(CERO),
            cantidad_cajas(CERO),
            id_ganador(ID_GANADOR),
            id_mapa(mapa){}

    // Verifica la existencia de la id recibida por parametro.
    bool chequear_id(const int& id) {
        return std::any_of(info_patos.cbegin(), info_patos.cend(), MismoID(id));
    }

    // Agrega la informacion de un pato en el vector de informacion de todos los patos.
    // Utilizando un puntero al pato.
    void agregar_info_pato(Pato* p) {
        if (!chequear_id(p->id_jugador)) {
            InformacionPato nuevo_pato(p);
            this->info_patos.push_back(nuevo_pato);
            this->cantidad_jugadores++;
        }
    }

    // Agrega la informacion de un pato en el vector de informacion de todos los patos.
    // Utilizando una referencia a la informacion del pato.
    void agregar_info_pato(const InformacionPato& info) {
        if (!chequear_id(info.id)) {
            this->info_patos.push_back(info);
            this->cantidad_jugadores++;
        }
    }

    // Agrega la informacion de un arma (recibida por referencia constante) en particular al vector.
    void agregar_arma(const InformacionArma& info) {
        info_armas.push_back(info);
        this->cantidad_armas++;
    }

    // Agrega la informacion de un arma (recibida como puntero) en particular al vector.
    void agregar_arma(Arma* a) {
        InformacionArma nueva(a);
        info_armas.push_back(nueva);
        this->cantidad_armas++;
    }

    // Agrega la informacion de una bala disparada (recibida como un puntero)
    void agregar_bala(Municion* m){
        InformacionBala nueva(m);
        info_balas.push_back(nueva);
        this->cantidad_balas++;
    }

    // Agrega la informacion de una bala (recibida por referencia constante) en particular al vector.
    void agregar_bala(const InformacionBala& bala){
        info_balas.push_back(bala);
        this->cantidad_balas++;
    }

    void definir_ganador(const int& id){
        this->id_ganador = id;
    }

    // Vacia la informacion de los patos.
    void vaciar() { this->info_patos.clear(); }
};

#endif  // ESTADO_JUEGO_H_
