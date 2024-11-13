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

// 'struct' que encapsula la informacion del pato para enviarla en el estado.
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
            estado(p->estado_actual) {}

    // Constructor del struct con parametros.
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

// 'struct' que encapsula la informacion de todas las armas del juego.
struct InformacionArma {
    int id_arma;
    posicion_t posicion;

    // Primera variante del constructor del struct.
    explicit InformacionArma(Arma* a): id_arma(a->id_arma), posicion(a->posicion_spawn) {}

    // Segunda variante del constructor del struct.
    explicit InformacionArma(uint8_t id, float x, float y): id_arma(id), posicion(x, y) {}

    // Tercera variante del constructor del struct.
    explicit InformacionArma(uint8_t id, posicion_t pos): id_arma(id), posicion(pos) {}
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
    std::vector<InformacionPato> info_patos;
    std::vector<InformacionArma> info_armas;

    // Constructor del struct.
    EstadoJuego():
            cantidad_jugadores(CERO),
            cantidad_armas(CERO),
            cantidad_balas(CERO),
            cantidad_armaduras(CERO),
            cantidad_cascos(CERO),
            cantidad_cajas(CERO) {}

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

    // Agrega la informacion de un arma (recibida pro copia) en particular al vector.
    void agregar_arma(const InformacionArma info) {
        info_armas.push_back(info);
        this->cantidad_armas++;
    }

    // Agrega la informacion de un arma (recibida como puntero) en particular al vector.
    void agregar_arma(Arma* a) {
        InformacionArma nueva(a);
        info_armas.push_back(nueva);
        this->cantidad_armas++;
    }

    // Convierte el estado de juego en un texto, para verificar si funcionamiento sin interfaz
    // grafica.
    std::string to_string() {
        std::ostringstream oss;
        oss << "Jugadores : " << cantidad_jugadores << ". Armas: " << cantidad_armas << ". Balas: ";
        oss << cantidad_balas << "\n. Armaduras: " << cantidad_armaduras
            << ". Cascos: " << cantidad_cascos;
        oss << ". Cajas: " << cantidad_cajas << "\n";

        for (InformacionPato info: info_patos) {
            oss << "PATO: \n ID: " << info.id << ". POSICION: (" << info.posicion.coordenada_x
                << "," << info.posicion.coordenada_y << ")\n";
            oss << "VIVO: " << (info.vivo ? "SI" : "NO")
                << ". TIENE ARMA: " << (info.arma ? "SI" : "NO")
                << ". ID ARMA: " << info.id_arma_equipada;
            oss << "\nCASCO: " << (info.casco ? "SI" : "NO")
                << ". ARMADURA: " << (info.armadura ? "SI" : "NO");
            std::string sentido;
            switch (info.orientacion) {
                case DERECHA:
                    sentido = "Derecha";
                    break;

                case IZQUIERDA:
                    sentido = "Izquierda";
                    break;

                default:
                    sentido = "Arriba";
                    break;
            }

            std::string estado_pato;
            switch (info.estado) {
                case PARADO:
                    estado_pato = "Parado";
                    break;

                case AGACHADO:
                    estado_pato = "Agachado";
                    break;

                case SALTANDO:
                    estado_pato = "Saltando";
                    break;

                case CAYENDO:
                    estado_pato = "Cayendo";
                    break;

                case ALETEANDO:
                    estado_pato = "Aleteando";
                    break;

                case CAMINANDO:
                    estado_pato = "Caminando";
                    break;
            }

            oss << "\nSENTIDO: " << sentido << ". ESTADO ACTUAL: " << estado_pato;
            oss << "\n---------------------------------\n";
        }

        for (int i = 0; i < cantidad_armas; i++) {
            oss << i << ". ID arma: " << this->info_armas[i].id_arma;
            oss << "\nPosicion: " << this->info_armas[i].posicion.to_string();
            oss << "----------------------------------\n";
        }

        return oss.str();
    }

    // Vacia la informacion de los patos.
    void vaciar() { this->info_patos.clear(); }
};

#endif  // ESTADO_JUEGO_H_