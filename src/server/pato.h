// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef SERVER_PATO_H_
#define SERVER_PATO_H_

#include <iostream>
#include <mutex>

#include "../common/estado_fisico.h"
#include "../common/informacion_arma.h"
#include "../common/orientacion.h"
#include "../common/posicion.h"
#include "server/arma.h"
#include "server/mapa.h"

#include "caja.h"

#define CERO 0
#define CINCO 5

// 'Enum' utilizado para encapsular los sonidos del pato.
enum sonido_e { SILENCIO, HACIENDO_CUAK, DISPARANDO };

// La clase 'Pato' implementa toda la logica del
// pato en el transcurso del juego.
class Pato {
    friend struct EstadoJuego;
    friend class Gameloop;
    friend struct InformacionPato;
    friend struct MismoID;

private:
    int id_jugador;
    posicion_t posicion;
    bool vivo;
    bool posee_arma;
    bool posee_armadura;
    bool posee_casco;
    orientacion_e orientacion;
    Arma* arma_equipada;
    estado_pato_e estado_actual;
    int iteraciones_subiendo;
    int iteraciones_desde_aleteo;
    bool inmortal;
    sonido_e sonido;
    int rondas_ganadas;
    int iteraciones_mirando_para_arriba;
    orientacion_e orientacion_anterior;
    std::mutex mtx;

    // Verifica si el pato puede moverse en la direccion especificada.
    bool chequeo_movimiento(Mapa& mapa, const orientacion_e& direccion);

    // Verifica y actualiza el estado del pato segun su estado actual.
    void chequear_estado(Mapa& mapa);

    // Mueve al pato en la direccion especificada, considerando colisiones y limites del mapa.
    bool mover(Mapa& mapa, const orientacion_e& direccion, bool disparo);

    // Hace que el pato salte, cambiando su estado y posicion.
    void saltar();

    // Hace que el pato aletee si esta cayendo.
    void aletear();

    // Devuelve true si el pato tiene un arma equipada.
    bool tiene_arma();

    // Hace que el pato se agache.
    void agacharse();

    // Cambia la orientacion del pato a la nueva direccion especificada.
    void cambiar_orientacion(const orientacion_e& nueva_orientacion);

    // El pato suelta el arma equipada.
    void soltar_arma();

    // Devuelve true si el pato esta vivo.
    bool esta_vivo();

    // El pato agarra armadura, actualizando su estado.
    bool agarrar_armadura();

    // El pato agarra un casco, actualizando su estado.
    bool agarrar_casco();

    // Actualiza la posicion del pato al caer, considerando el mapa.
    void caer(Mapa& mapa);

    // Hace que el pato reciba un disparo, afectando su estado.
    void recibir_disparo();

    // Hace que el pato dispare su arma equipada, si tiene una.
    bool disparar(Mapa& mapa);

    // Obtiene el 'id' del arma equipada.
    int obtener_id_arma() { return arma_equipada ? arma_equipada->obtener_id() : CERO; }

    // Verifica si hay una pared en la direccion especificada desde la posicion dada.
    static bool buscar_pared(Mapa& mapa, const orientacion_e& direccion,
                             const posicion_t& posicion_a_chequear);

    // De ser posible, hace le 'Pickup' del item looteable en el piso.
    void pickup(std::vector<InformacionArma>& armas_tiradas,
                std::vector<posicion_t>& cascos_tirados, std::vector<posicion_t>& armaduras_tiradas,
                std::vector<Spawn>& spawns, std::vector<Municion>& balas_volando,
                const std::vector<Caja>& cajas);

    // Equipa el arma recibida por parametro al pato.
    void equipar_arma(const int& id_arma, std::vector<Municion>& balas_volando);

    // 'Cheat' que aumenta la cantidad de rondas ganadas por el 'Pato'.
    void aumentar_rondas_ganadas() { this->rondas_ganadas += CINCO; }

public:
    // Constructor de la clase.
    explicit Pato(int id, Mapa& mapa);

    // Devuelve la posicion actual del pato.
    posicion_t obtener_posicion();

    // Devuelve la orientacion actual del pato.
    orientacion_e obtener_orientacion();

    // Devuelve true si el pato tiene armadura equipada.
    bool tiene_armadura();

    // Devuelve true si el pato tiene casco equipado.
    bool tiene_casco();

    // Controla la logica previa a la ejecucion de comandos.
    void control_pre_comando(Mapa& mapa, std::vector<Municion>& balas_volando);

    // Realiza una accion segun el comando recibido.
    void realizar_accion(const int& accion, Mapa& mapa, std::vector<InformacionArma>& armas_tiradas,
                         std::vector<posicion_t>& cascos_tirados,
                         std::vector<posicion_t>& armaduras_tiradas, std::vector<Spawn>& spawns,
                         std::vector<Municion>& balas_volando, const std::vector<Caja>& cajas);

    // Resetea el estado del pato en el mapa al cambiar de ronda.
    void resetear(Mapa& mapa);

    // Destructor de la clase.
    ~Pato();

    // Deshabilito las copias.
    Pato(const Pato&) = delete;
    Pato& operator=(const Pato&) = delete;

    // Permito el movimiento del objeto.
    Pato(Pato&&) = default;
    Pato& operator=(Pato&&) = default;
};

#endif  // SERVER_PATO_H_
