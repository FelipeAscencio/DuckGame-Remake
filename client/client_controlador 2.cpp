#include "client_controlador.h"

using namespace SDL2pp;

Controlador::Controlador() {}

void Controlador::manejarEventos(bool& jugador_activo, int& estado) {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            jugador_activo = false;
        } else if (sdlEvent.type == SDL_KEYDOWN) {    // Detecta cuando una tecla es presionada
            if (sdlEvent.key.keysym.sym == SDLK_q) {  // Verifica si la tecla presionada es "e"
                estado = 0;                           // Cambia el valor de "estado" a 0
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_w) {  // Verifica si la tecla presionada es "e"
                estado = 1;       // Cambia el valor de "estado" a 1
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_e) {  // Verifica si la tecla presionada es "e"
                estado = 2;       // Cambia el valor de "estado" a 2
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_r) {  // Verifica si la tecla presionada es "e"
                estado = 3;       // Cambia el valor de "estado" a 3
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_a) {  // Verifica si la tecla presionada es "e"
                estado = 4;       // Cambia el valor de "estado" a 4
            }
        }
    }
}
