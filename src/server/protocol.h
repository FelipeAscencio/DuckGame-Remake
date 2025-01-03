// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <iostream>
#include <list>
#include <vector>

#include <netinet/in.h>

#include "../common/comando.h"
#include "../common/estado_juego.h"
#include "../common/socket.h"

namespace ServerProtocol {

// La clase 'Protocol' implementa toda la logica del
// protocolo del lado del 'Server'.
class Protocol {
private:
    Socket& s;

    // Serializa la informacion de las cajas.
    std::vector<uint8_t> serializar_caja(const InformacionCaja& caja);

    // Serializa la informacion de los cascos y las armaduras.
    std::vector<uint8_t> serializar_casco_o_armadura(const posicion_t& pos, bool casco);

    // Serializa la informacion de el mapa.
    std::vector<uint8_t> serializar_mapa(const int& mapa);

    // Serializa la informacion del ganador. Si esta en la mitad de una ronda, envia un valor dummy
    std::vector<uint8_t> serializar_ganador(const int& id);

    // Serializa la informacion de una bala disparada (id del arma, posicion actual e inclinacion)
    std::vector<uint8_t> serializar_bala(const InformacionBala& info_bala);

    // Serializa la informacion de un pato (incluye posicion, equipo, estado y otros atributos).
    std::vector<uint8_t> serializar_pato(const InformacionPato& info_pato);

    // Serializa las cantidades generales del juego (numero de jugadores, armas, balas, etc.).
    std::vector<uint8_t> serializar_cantidades(const EstadoJuego& estado_actual);

    // Serializa la informacion de un arma, incluyendo su posicion en el mapa.
    std::vector<uint8_t> serializar_armas(const InformacionArma& info_arma);

    // Envia los bytes serializados a traves de la conexion, asegurandose de que no se haya cerrado.
    bool _enviar(const std::vector<uint8_t>& bytes);

public:
    // Constructor de la clase.
    explicit Protocol(Socket& skt);

    // Recibe un comando del cliente y lo procesa, llenando la estructura de comando
    // correspondiente.
    bool recibir(comando_t& cmd, const int& id_cliente);

    // Serializa y envia el estado completo del juego, incluyendo jugadores, armas y cantidades.
    bool enviar(const EstadoJuego& estado_actual);

    // Verifica si una accion dada es valida dentro del rango permitido.
    static bool accion_valida(const uint8_t& accion);

    // Deshabilito las copias.
    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    // Permito el movimiento del objeto.
    Protocol(Protocol&&) = default;
    Protocol& operator=(Protocol&&) = default;
};

};  // namespace ServerProtocol

#endif  // SERVER_PROTOCOL_H_
