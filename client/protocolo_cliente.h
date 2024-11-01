// Copyright 2024 Axel Zielonka y Felipe Ascensio
#ifndef CLIENT_PROTOCOLO_CLIENTE_H_
#define CLIENT_PROTOCOLO_CLIENTE_H_

#include <iostream>
#include <vector>

#include "../common/comando.h"
#include "../common/estado_juego.h"
#include "../common/socket.h"

struct ErrorConstructor: public std::runtime_error {
    ErrorConstructor():
            std::runtime_error("Error en la creacion del protocolo, fallo el socket para recibir "
                               "el ID del cliente") {}
};

class ProtocoloCliente {
    friend class Client;
private:
    Socket& s;
    int id_cliente;

    bool procesar_leido(const uint8_t& leido, EstadoJuego& estado_actual);

    bool procesar_patos(EstadoJuego& estado_actual);

    bool procesar_cantidades(EstadoJuego& estado_actual);

    uint8_t parsear_comando(char accion);

public:
    // explicit ProtocoloCliente(const char* hostname, const char* servname);

    explicit ProtocoloCliente(Socket& s);


    bool enviar(const char& accion);

    bool recibir(EstadoJuego& estado_actual);

    int get_id() { return this->id_cliente; }
};

#endif  // CLIENT_PROTOCOLO_CLIENTE_H_
