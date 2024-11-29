// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef CLIENT_CONTROLADOR_H
#define CLIENT_CONTROLADOR_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "../common/queue.h"

// Suprimimos el reporte en 'CPPLINT' de los 'namespaces'.
using namespace SDL2pp;  // NOLINT(build/namespaces)

// La clase 'Controlador' implementa la logica
// del control de los eventos del 'Cliente'.
class Controlador {
private:
    Queue<char>& cola_eventos;

public:
    // Constructor de la clase.
    explicit Controlador(Queue<char>& cola_enviador);

    // Esta funcion maneja los eventos que el 'Cliente' efectua durante el juego.
    void manejar_eventos(bool& jugador_activo);

    // Deshabilito las copias.
    Controlador(const Controlador&) = delete;
    Controlador& operator=(const Controlador&) = delete;

    // Permito el movimiento del objeto.
    Controlador(Controlador&&) = default;
    Controlador& operator=(Controlador&&) = default;
};

#endif  // CLIENT_CONTROLADOR_H
