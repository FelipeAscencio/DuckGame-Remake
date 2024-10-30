#ifndef CLIENT_MOCK_H
#define CLIENT_MOCK_H

#include <iostream>

#include "../common/estado_juego.h"

#include "protocolo_cliente.h"

class ClientMock {

private:
    ProtocoloCliente protocolo;

    void loop_juego();

    char leer_entrada();

    bool realizar_accion(const char& accion);

    bool recibir_respuesta_juego(EstadoJuego& estado_actual);

public:
    explicit ClientMock(const char* hostname, const char* servname);

    void start();
};


#endif
