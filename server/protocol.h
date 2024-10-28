#ifndef PROTOCOL_H
#define PROTOCOL_H


#include <iostream>
#include <list>

#include "../common/socket.h"

#include "../common/comando.h"
#include "../common/estado_juego.h"
#include "pato.h"
namespace ServerProtocol {

class Protocol {
private:
    Socket& s;

    std::vector<uint8_t> serializar_pato(const informacion_pato_t& estado_actual);

    std::vector<uint8_t> serializar_cantidades(const estado_juego_t& estado_actual);

public:
    explicit Protocol(Socket& skt);

    bool recibir(comando_t& cmd);

    bool enviar(const estado_juego_t& estado_actual);

    static bool accion_valida(const uint8_t& accion);
};

};  // namespace ServerProtocol

#endif
