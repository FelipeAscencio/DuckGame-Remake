#include "client_handler.h"

#define MENOS_UNO -1
#define ANCHO_MIN 640
#define ALTO_MIN 480
#define DUCK_GAME_STR "Duck Game"

using namespace SDL2pp;

Client::Client(const char* hostname, const char* servicio):
        hostname(hostname), servicio(servicio), jugador_activo(true), controlador(), dibujador() {}

void Client::controlar_loop_juego() {
    SDL sdl(SDL_INIT_VIDEO);
    Window window(DUCK_GAME_STR, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_MIN, ALTO_MIN, SDL_WINDOW_RESIZABLE);
    Renderer renderer(window, MENOS_UNO, SDL_RENDERER_ACCELERATED);

    while (this->jugador_activo) {
        controlador.manejarEventos(this->jugador_activo);
        dibujador.renderizar(renderer, window);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
