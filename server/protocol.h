#ifndef PROTOCOL_H
#define PROTOCOL_H


#include <iostream>

#include "../common/socket.h"

namespace ServerProtocol {

typedef struct Comando {
    uint8_t id_cliente;
    uint8_t accion;
} comando_t;

class Protocol {
private:
    Socket& s;

public:
    explicit Protocol(Socket& skt);

    bool receive(comando_t& cmd);
};

};  // namespace ServerProtocol

#endif
