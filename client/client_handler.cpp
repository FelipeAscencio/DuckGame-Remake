#include "client_handler.h"

#define MENOS_UNO -1
#define ANCHO_MIN 960
#define ALTO_MIN 720
#define DUCK_GAME_STR "Duck Game"
#define RUTA_MAPA_1 "/mapa1.png"

using namespace SDL2pp;

Client::Client(const char* hostname, const char* servicio):
        hostname(hostname), servicio(servicio), jugador_activo(true), controlador(), estado(0) {}

void Client::controlar_loop_juego() {
    SDL sdl(SDL_INIT_VIDEO);
    Window window(DUCK_GAME_STR, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_MIN,
                  ALTO_MIN, SDL_WINDOW_SHOWN);
    Renderer renderer(window, MENOS_UNO, SDL_RENDERER_ACCELERATED);
    std::string ruta_mapa = RUTA_MAPA_1;
    dibujador.emplace(renderer, ruta_mapa);

    while (this->jugador_activo) {
        controlador.manejarEventos(this->jugador_activo, this->estado);
        if (dibujador) {
            dibujador->renderizar(renderer, window, this->estado);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
