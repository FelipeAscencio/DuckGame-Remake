#ifndef PROTOCOL_H
#define PROTOCOL_H


#include <iostream>
#include <list>

#include "../common/socket.h"

#include "comando.h"
#include "pato.h"
#include "estado_juego.h"
namespace ServerProtocol {

class Protocol {
private:
    Socket& s;

    std::vector<uint8_t> serializar(const estado_juego_t& estado_actual, int indice);

public:
    explicit Protocol(Socket& skt);

    bool recibir(comando_t& cmd);

    bool enviar(const estado_juego_t& estado_actual);

    static bool accion_valida(const uint8_t& accion);
};

};  // namespace ServerProtocol

#endif
