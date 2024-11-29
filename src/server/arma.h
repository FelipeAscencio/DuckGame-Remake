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

#define ID_PP_LASER 1
#define ID_AK47 2
#define ID_MAGNUM 3
#define ID_SHOTGUN 4
#define ID_SNIPER 5

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
    const int municiones_iniciales;
    int municiones;
    bool retroceso;
    posicion_t posicion_spawn;
    bool agarrada;
    bool soltada;
    std::vector<Municion> balas;

    // Ajusta la posicion inicial de la bala, haciendo que no sea exactamente la posicion del arma, segun la direccion
    posicion_t ajustar_posicion_disparo(const orientacion_e& direccion);

    // Verifica si el arma puede ser agarrada nuevamente.
    bool puede_agarrarse();

    // Realiza el chequeo de avance de las balas
    virtual void control_atributos(Mapa& mapa);

    // Elimina la bala en la posicion 'indice'
    virtual void eliminar_bala(const int& indice);

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

    // Devuelve el 'id' del Arma.
    int obtener_id() const { return id_arma; }

    // Restaura la cantidad de municiones restantes del arma
    void recargar();

    // Destructor de la clase.
    virtual ~Arma();

    // Deshabilito las copias.
    Arma(const Arma&) = delete;
    Arma& operator=(const Arma&) = delete;

    // Permito el movimiento del objeto.
    Arma(Arma&&) = default;
    Arma& operator=(Arma&&) = default;
};

#endif  // ARMA_H
