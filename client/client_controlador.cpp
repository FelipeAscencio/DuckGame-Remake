#include "client_controlador.h"

using namespace SDL2pp;

Controlador::Controlador() {}

void Controlador::manejarEventos(bool &jugador_activo) {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            jugador_activo = false;
        }
    }
}
