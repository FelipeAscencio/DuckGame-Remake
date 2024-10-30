#include "client_handler.h"

#define CERO 0
#define MENOS_UNO -1
#define ANCHO_MIN 960
#define ALTO_MIN 720
#define VOLUMEN_MUSICA 20
#define FRECUENCIA_HZ 44100
#define BUFFER_AUDIO 2048
#define AUDIO_ESTEREO 2
#define DUCK_GAME_STR "Duck Game"
#define RUTA_MAPA_1 "/mapa1.png"
#define MUSICA_FONDO "/arcade-song.mp3"
#define ERROR_INICIAR_MIX "Error al inicializar SDL_mixer: "
#define ERROR_CARGAR_MUSICA "Error al cargar la música de fondo: "

using namespace SDL2pp;

Client::Client(const char* hostname, const char* servicio):
        hostname(hostname), servicio(servicio), jugador_activo(true), controlador(), estado(0) {}

void Client::controlar_loop_juego() {
    if (Mix_OpenAudio(FRECUENCIA_HZ, MIX_DEFAULT_FORMAT, AUDIO_ESTEREO, BUFFER_AUDIO) < CERO) {
        std::cerr << ERROR_INICIAR_MIX << Mix_GetError() << std::endl;
    }
    Mix_Music* musica_fondo = Mix_LoadMUS(DATA_PATH MUSICA_FONDO);
    if (!musica_fondo) {
        std::cerr << ERROR_CARGAR_MUSICA << Mix_GetError() << std::endl;
    } else {
        Mix_VolumeMusic(VOLUMEN_MUSICA);
        Mix_PlayMusic(musica_fondo, MENOS_UNO);
    }

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

    Mix_FreeMusic(musica_fondo);
    Mix_CloseAudio();
}
