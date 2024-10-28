#ifndef PROTOCOLO_CLIENTE_H
#define PROTOCOLO_CLIENTE_H


#include <iostream>
#include "../common/socket.h"
#include "../common/comando.h"
#include "../common/estado_juego.h"

class ProtocoloCliente {
    private:
        Socket& s;

        bool procesar_leido(const uint8_t& leido, estado_juego_t& estado_actual);

        bool procesar_patos(estado_juego_t& estado_actual);

        bool procesar_cantidades(estado_juego_t& estado_actual);

    public:
        ProtocoloCliente(Socket& skt);

        bool enviar(comando_t& cmd);

        bool recibir(estado_juego_t& estado_actual);

};

#endif