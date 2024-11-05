// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef CLIENT_PROTOCOLO_CLIENTE_H_
#define CLIENT_PROTOCOLO_CLIENTE_H_

#include <iostream>
#include <map>
#include <vector>

#include "../common/comando.h"
#include "../common/estado_juego.h"
#include "../common/socket.h"

// Struct de error en la construccion del 'Protocolo'.
struct ErrorConstructor: public std::runtime_error {
    ErrorConstructor():
            std::runtime_error("Error en la creacion del protocolo, fallo el socket para recibir "
                               "el ID del cliente") {}
};

// La clase 'ProtocoloCliente' controla la comunicacion
// del 'Cliente' con el 'Server'.
class ProtocoloCliente {
    friend class Client;

private:
    Socket& s;
    int id_cliente;

    // Procesa el dato 'leido' y ejecuta la accion correspondiente en el 'estado_actual'.
    bool procesar_leido(const uint8_t& leido, EstadoJuego& estado_actual);

    // Procesa y carga la informacion de los patos en el 'estado_actual'.
    bool procesar_patos(EstadoJuego& estado_actual);

    // Asigna al 'estado_actual' las cantidades de cada elemento del juego.
    bool procesar_cantidades(EstadoJuego& estado_actual);

    // Procesa y carga la informacion de las armas en el 'estado_actual'.
    bool procesar_armas(EstadoJuego& estado_actual);

    // Convierte el comando en formato 'char' al byte correspondiente.
    uint8_t parsear_comando(char accion);

public:
    // Constructor de la clase.
    explicit ProtocoloCliente(Socket& s);

    // Envia la accion del 'Cliente' al 'Server'.
    bool enviar(const char& accion);

    // Recibe el estado del juego que el 'Server' envia.
    bool recibir(EstadoJuego& estado_actual);

    // Deshabilito las copias.
    ProtocoloCliente(const ProtocoloCliente&) = delete;
    ProtocoloCliente& operator=(const ProtocoloCliente&) = delete;

    // Permito el movimiento del objeto.
    ProtocoloCliente(ProtocoloCliente&&) = default;
    ProtocoloCliente& operator=(ProtocoloCliente&&) = default;
};

#endif  // CLIENT_PROTOCOLO_CLIENTE_H_
