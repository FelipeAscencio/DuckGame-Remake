// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef ARMA_H
#define ARMA_H

#include <iostream>
#include <string>
#include <vector>

#include "../common/orientacion.h"
#include "../common/posicion.h"

#include "mapa.h"
#include "municion.h"

#define ID_GRANADA 1
#define ID_BANANA 2
#define ID_PP_LASER 3
#define ID_LASER_RIFLE 4
#define ID_AK47 5
#define ID_DUEL_PISTOL 6
#define ID_COWBOY_PISTOL 7
#define ID_MAGNUM 8
#define ID_SHOTGUN 9
#define ID_SNIPER 10

// La clase 'Arma' encapsula la logica compartida de las
// armas para que luego cada arma en particular la implemente.
class Arma {
    friend struct InformacionArma;
    friend struct EstadoJuego;
    friend class Pato;
    friend class Gameloop;

protected:
    const int id_arma;
    const std::string nombre;
    int alcance;
    int municiones;
    bool retroceso;
    posicion_t posicion_spawn;
    bool agarrada;
    bool soltada;

    // Verifica si el arma puede ser agarrada nuevamente.
    bool puede_agarrarse();

    std::vector<Municion*> balas;

public:
    // Constructor de la clase.
    Arma(const int& id_arma, const std::string& nombre, const int& alcance, const int& municiones,
         bool tiene_retroceso, posicion_t posicion_inicial);

    // Metodo virtual, implementado en cada arma.
    virtual bool disparar(const orientacion_e& direccion, Mapa& mapa) = 0;

    // Realiza el chequeo de rango y paredes para cada una de las balas disparadas 
    void chequeo_balas(Mapa& mapa);

    // Marca el arma como "agarrada" por un jugador.
    void agarrar();

    // Marca el arma como "soltada" y la libera del estado de "agarrada".
    void soltar();

    // Indica si el arma tiene retroceso.
    bool tiene_retroceso();

    // Devuelve el alcance maximo del arma.
    int obtener_alcance();

    // Retorna el numero de municiones restantes en el arma.
    int municiones_restantes();

    // Verifica si el arma esta actualmente en uso.
    bool en_uso();

    // Devuelve la posicion inicial del arma al momento de su aparicion.
    posicion_t obtener_posicion_inicial();

    int obtener_id() const { return id_arma; }

    virtual ~Arma();
};

#endif  // ARMA_H
