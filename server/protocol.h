// Copyright 2024 Axel Zielonka y Felipe Ascensio
#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <iostream>
#include <list>
#include <vector>

#include "../common/comando.h"
#include "../common/estado_juego.h"
#include "../common/socket.h"

namespace ServerProtocol {

class Protocol {
private:
    Socket& s;

    std::vector<uint8_t> serializar_pato(const InformacionPato& info_pato);
    std::vector<uint8_t> serializar_cantidades(const EstadoJuego& estado_actual);
    std::vector<uint8_t> serializar_armas(const InformacionArma& info_arma);
    bool _enviar(const std::vector<uint8_t>& bytes);

public:
    explicit Protocol(Socket& skt);

    bool recibir(comando_t& cmd, const int& id_cliente);

    bool enviar(const EstadoJuego& estado_actual);

    static bool accion_valida(const uint8_t& accion);
};

};  // namespace ServerProtocol

#endif  // SERVER_PROTOCOL_H_
