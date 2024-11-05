#include "client_controlador.h"

#define COMANDO_EXIT 'X'
#define COMANDO_DERECHA 'D'
#define COMANDO_IZQUIERDA 'A'
#define COMANDO_AGACHAR 'S'
#define COMANDO_MIRAR_ARRIBA 'W'
#define COMANDO_SALTAR ' '
#define COMANDO_DISPARAR 'J'
#define COMANDO_AGARRAR 'K'

using namespace SDL2pp;

Controlador::Controlador(Queue<char>& cola_enviador) : cola_eventos(cola_enviador) {}

void Controlador::manejar_eventos(bool& jugador_activo) {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            jugador_activo = false;
            cola_eventos.try_push(COMANDO_EXIT);
        } else if (sdlEvent.type == SDL_KEYDOWN) {
            if (sdlEvent.key.keysym.sym == SDLK_d) {
                cola_eventos.try_push(COMANDO_DERECHA);
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_a) {
                cola_eventos.try_push(COMANDO_IZQUIERDA);
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_s) {
                cola_eventos.try_push(COMANDO_AGACHAR);
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_w) {
                cola_eventos.try_push(COMANDO_MIRAR_ARRIBA);
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_SPACE) {
                cola_eventos.try_push(COMANDO_SALTAR);
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_j){
                cola_eventos.try_push(COMANDO_DISPARAR);
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_k){
                cola_eventos.try_push(COMANDO_AGARRAR);
            }
        }
    }
}
