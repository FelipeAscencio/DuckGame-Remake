#include "client_controlador.h"

using namespace SDL2pp;

Controlador::Controlador() {}

void Controlador::manejar_eventos(bool& jugador_activo, int& estado) {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            jugador_activo = false;
        } else if (sdlEvent.type == SDL_KEYDOWN) {
            if (sdlEvent.key.keysym.sym == SDLK_q) {
                estado = 0;
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_w) {
                estado = 1;
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_e) {
                estado = 2;
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_r) {
                estado = 3;
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_a) {
                estado = 4;
            }
        }
    }
}
