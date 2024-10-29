// Copyright 2024 Axel Zielonka y Felipe Ascensio
#ifndef COMMON_ESTADO_JUEGO_H_
#define COMMON_ESTADO_JUEGO_H_

#include <algorithm>
#include <iostream>
#include <vector>

#include "../server/arma.h"
#include "../server/pato.h"
#include "common/estado_fisico.h"
#include "common/orientacion.h"
#include "common/posicion.h"

struct InformacionPato {
    int id;
    posicion_t posicion;
    bool vivo;
    bool arma;
    int id_arma_equipada;
    bool casco;
    bool armadura;
    orientacion_e orientacion;
    estado_pato_e estado;

    explicit InformacionPato(Pato& p):
            id(p.id_jugador),
            posicion(p.posicion),
            vivo(p.vivo),
            arma(p.posee_arma),
            id_arma_equipada(p.obtener_id_arma()),
            casco(p.posee_casco),
            armadura(p.posee_armadura),
            orientacion(p.orientacion),
            estado(p.estado_actual) {}

    explicit InformacionPato(const uint8_t& id_pato, const posicion_t& pos, bool esta_vivo,
                             bool tiene_arma, const uint8_t& id_arma, bool tiene_casco,
                             bool tiene_armadura, const orientacion_e& orientacion_pato,
                             const estado_pato_e& estado_pato):
            id(id_pato),
            posicion(pos),
            vivo(esta_vivo),
            arma(tiene_arma),
            id_arma_equipada(id_arma),
            casco(tiene_casco),
            armadura(tiene_armadura),
            orientacion(orientacion_pato),
            estado(estado_pato) {}
};

struct MismoID {
    const int id;
    explicit MismoID(int id_buscado): id(id_buscado) {}
    bool operator()(const InformacionPato& i) const { return i.id == id; }
    bool operator()(const Pato& p) const { return p.id_jugador == id; }
};

struct EstadoJuego {
    int cantidad_jugadores;
    int cantidad_armas;
    int cantidad_balas;
    int cantidad_armaduras;
    int cantidad_cascos;
    int cantidad_cajas;
    std::vector<InformacionPato> info_patos;

    EstadoJuego():
            cantidad_jugadores(0),
            cantidad_armas(0),
            cantidad_balas(0),
            cantidad_armaduras(0),
            cantidad_cascos(0),
            cantidad_cajas(0) {}

    bool chequear_id(const int& id) {
        return std::any_of(info_patos.cbegin(), info_patos.cend(), MismoID(id));
    }

    void agregar_info_pato(Pato& p) {
        if (!chequear_id(p.id_jugador)) {
            InformacionPato nuevo_pato(p);
            info_patos.push_back(nuevo_pato);
            cantidad_jugadores++;
        }
    }

    void agregar_info_pato(const InformacionPato& info) {
        if (!chequear_id(info.id)) {
            info_patos.push_back(info);
            cantidad_jugadores++;
        }
    }
};

#endif  // COMMON_ESTADO_JUEGO_H_