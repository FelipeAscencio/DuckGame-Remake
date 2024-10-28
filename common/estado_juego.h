#ifndef ESTADO_JUEGO_H
#define ESTADO_JUEGO_H

#include <iostream>
#include <vector>

#include "posicion.h"

#include "../server/armas/arma.h"
#include "estado_fisico.h"
#include "orientacion.h"

// struct juego total {
/*
    struct informacion patos
    struct informacion armas tiradas
    struct informacion cjas
    ...
*/

typedef struct InformacionPato{
    int id;
    posicion_t posicion;
    bool vivo;
    bool arma;
    int id_arma_equipada;
    bool casco;
    bool armadura;
    orientacion_e orientacion;
    estado_pato_e estado;

    InformacionPato(const int& id_pato, const posicion_t& posicion_actual, bool esta_vivo, bool tiene_arma, int id_arma, bool tiene_casco, bool tiene_armadura, const orientacion_e& mirando_para, const estado_pato_e& estado_actual) :
        id(id_pato), posicion(posicion_actual), vivo(esta_vivo), arma(tiene_arma), id_arma_equipada(id_arma), casco(tiene_casco), armadura(tiene_armadura), orientacion(mirando_para), estado(estado_actual) {}
} informacion_pato_t;

typedef struct EstadoJuego {
    int cantidad_jugadores;
    int cantidad_armas;
    int cantidad_balas;
    int cantidad_armaduras;
    int cantidad_cascos;
    int cantidad_cajas;
    std::vector<informacion_pato_t> info_patos;

    EstadoJuego() : cantidad_jugadores(0), cantidad_armas(0), cantidad_balas(0), cantidad_armaduras(0), cantidad_cascos(0), cantidad_cajas(0){}

    void agregar_info_pato(Pato& p){
        bool id_existente = false;
        for (auto& i: info_patos){
            if (i.id == p.id_jugador){
                id_existente = true;
                break;
            } 
        }
        if (!id_existente){
            int id_arma = p.arma_equipada ? p.arma_equipada->id_arma : 0;
            informacion_pato_t pato_actual(p.id_jugador, p.posicion, p.vivo, p.posee_arma, id_arma, p.posee_casco, p.posee_armadura, p.orientacion, p.estado_actual);
            cantidad_jugadores++;
        }
    }

    void agregar_info_pato(informacion_pato_t& info_pato){
        bool id_existente = false;
        for (auto& i: info_patos){
            if (i.id == info_pato.id){
                id_existente = true;
                break;
            } 
        }
        if (!id_existente){
            info_patos.push_back(info_pato);
            cantidad_jugadores++;
        }
    }
} estado_juego_t;


#endif
