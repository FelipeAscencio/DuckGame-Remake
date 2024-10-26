#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <chrono>
#include <thread>

#include "client_controlador.h"
#include "client_dibujador.h"

using namespace SDL2pp;

// La clase 'Client' implementa toda la logica de control
// de los eventos y el dibujo del 'Cliente'.
class Client {
private:
    const char* hostname;
    const char* servicio;
    bool jugador_activo;
    Controlador controlador;
    std::optional<Dibujador> dibujador;
    int estado;  // PROVISORIO PARA

public:
    // Constructor de la clase.
    explicit Client(const char* hostname, const char* servicio);

    // Maneja la secuencia de controlador y dibujo del 'Cliente'.
    void controlar_loop_juego();

    // Deshabilito las copias.
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    // Permito el movimiento del objeto.
    Client(Client&&) = default;
    Client& operator=(Client&&) = default;
};

#endif
